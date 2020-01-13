#!/usr/jens/dvl/mksh/mksh
LC_ALL=C PATH='/bin:.'; export LC_ALL PATH
test -n "$KSH_VERSION" || exit 1
set -A check_categories --  arge no-histfile stdout-ed,no-stderr-ed
pflag='/usr/jens/dvl/mksh/mksh'
sflag='./check.t'
usee=0 Pflag=0 uset=0 vflag=0 xflag=0
while getopts "C:e:fPp:s:t:v" ch; do case $ch {
(C)	check_categories[${#check_categories[*]}]=$OPTARG ;;
(e)	usee=1; eflag=$OPTARG ;;
(f)	check_categories[${#check_categories[*]}]=fastbox ;;
(P)	Pflag=1 ;;
(p)	pflag=$OPTARG ;;
(s)	sflag=$OPTARG ;;
(t)	uset=1; tflag=$OPTARG ;;
(v)	vflag=1 ;;
(*)	xflag=1 ;;
}
done
shift $((OPTIND - 1))
set -A args -- './check.pl' -p "$pflag" -s "$sflag"
x=
for y in "${check_categories[@]}"; do
x=$x,$y
done
if [[ -n $x ]]; then
args[${#args[*]}]=-C
args[${#args[*]}]=${x#,}
fi
if (( usee )); then
args[${#args[*]}]=-e
args[${#args[*]}]=$eflag
fi
(( Pflag )) && args[${#args[*]}]=-P
if (( uset )); then
args[${#args[*]}]=-t
args[${#args[*]}]=$tflag
fi
(( vflag )) && args[${#args[*]}]=-v
(( xflag )) && args[${#args[*]}]=-x	# force usage by synerr
print Testing mksh for conformance:
fgrep MirOS: './check.t'
fgrep MIRBSD './check.t'
print "This shell is actually:\n\t$KSH_VERSION"
print 'test.sh built for mksh R40 2012/04/06'
cstr='$os = defined $^O ? $^O : "unknown";'
cstr="$cstr"'print $os . ", Perl version " . $];'
for perli in $PERL perl5 perl no; do
if [[ $perli = no ]]; then
print Cannot find a working Perl interpreter, aborting.
exit 1
fi
print "Trying Perl interpreter '$perli'..."
perlos=$($perli -e "$cstr")
rv=$?
print "Errorlevel $rv, running on '$perlos'"
if (( rv )); then
print "=> not using"
continue
fi
if [[ -n $perlos ]]; then
print "=> using it"
break
fi
done
exec $perli "${args[@]}" "$@"
