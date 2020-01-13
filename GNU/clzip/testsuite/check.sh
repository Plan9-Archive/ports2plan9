#! /bin/sh
# check script for Clzip - Data compressor based on the LZMA algorithm
# Copyright (C) 2010, 2011 Antonio Diaz Diaz.
#
# This script is free software: you have unlimited permission
# to copy, distribute and modify it.

LC_ALL=C
export LC_ALL
objdir=`pwd`
testdir=`cd "$1" ; pwd`
LZIP="${objdir}"/clzip
framework_failure() { echo "failure in testing framework" ; exit 1 ; }

if [ ! -x "${LZIP}" ] ; then
	echo "${LZIP}: cannot execute"
	exit 1
fi

if [ -d tmp ] ; then rm -rf tmp ; fi
mkdir tmp
printf "testing clzip-%s..." "$2"
cd "${objdir}"/tmp

cat "${testdir}"/test.txt > in || framework_failure
fail=0

"${LZIP}" -t "${testdir}"/test_v0.lz || fail=1
printf .
"${LZIP}" -cd "${testdir}"/test_v0.lz > copy || fail=1
cmp in copy || fail=1
printf .

"${LZIP}" -t "${testdir}"/test_v1.lz || fail=1
printf .
"${LZIP}" -cd "${testdir}"/test_v1.lz > copy || fail=1
cmp in copy || fail=1
printf .

"${LZIP}" -t "${testdir}"/test_sync.lz || fail=1
printf .
"${LZIP}" -cd "${testdir}"/test_sync.lz > copy || fail=1
cmp in copy || fail=1
printf .

"${LZIP}" -cf "${testdir}"/test_v1.lz > out 2>/dev/null
if [ $? != 1 ] ; then fail=1 ; printf - ; else printf . ; fi
"${LZIP}" -cF "${testdir}"/test_v1.lz > out || fail=1
"${LZIP}" -cd out | "${LZIP}" -d > copy || fail=1
cmp in copy || fail=1
printf .

for i in s4Ki 0 1 2 3 4 5 6 7 8 9 ; do
	"${LZIP}" -k -$i in || fail=1
	mv -f in.lz copy.lz || fail=1
	printf "garbage" >> copy.lz || fail=1
	"${LZIP}" -df copy.lz || fail=1
	cmp in copy || fail=1
	printf .
done

for i in s4Ki 0 1 2 3 4 5 6 7 8 9 ; do
	"${LZIP}" -c -$i in > out || fail=1
	printf "g" >> out || fail=1
	"${LZIP}" -cd out > copy || fail=1
	cmp in copy || fail=1
	printf .
done

for i in s4Ki 0 1 2 3 4 5 6 7 8 9 ; do
	"${LZIP}" -$i < in > out || fail=1
	"${LZIP}" -d < out > copy || fail=1
	cmp in copy || fail=1
	printf .
done

for i in s4Ki 0 1 2 3 4 5 6 7 8 9 ; do
	"${LZIP}" -f -$i -o out < in || fail=1
	"${LZIP}" -df -o copy < out.lz || fail=1
	cmp in copy || fail=1
	printf .
done

"${LZIP}" -$i < in > anyothername || fail=1
"${LZIP}" -d anyothername || fail=1
cmp in anyothername.out || fail=1
printf .

echo
if [ ${fail} = 0 ] ; then
	echo "tests completed successfully."
	cd "${objdir}" && rm -r tmp
else
	echo "tests failed."
fi
exit ${fail}
