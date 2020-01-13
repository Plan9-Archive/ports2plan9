/*
Copyright (c) 2006 by Dan Kennedy.
Copyright (c) 2006 by Juliusz Chroboczek.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <sys/time.h>
#include <sys/select.h>
#include <poll.h>

int
poll(struct pollfd *fds, nfds_t nfds, int timo)
{
	struct timeval timeout, *toptr;
	fd_set ifds, ofds, efds, *ip, *op;
	int i, rc, fd;

	/* Set up the file-descriptor sets in ifds, ofds and efds. */
	FD_ZERO(&ifds);
	FD_ZERO(&ofds);
	FD_ZERO(&efds);
	for(i=0, op=ip=0; i<nfds; ++i){
		fds[i].revents = 0;
		if(fds[i].events & (POLLIN | POLLPRI)){
			ip = &ifds;
			FD_SET(fds[i].fd, ip);
		}
		if(fds[i].events & POLLOUT){
			op = &ofds;
			FD_SET(fds[i].fd, op);
		}
		FD_SET(fds[i].fd, &efds);
	}

	/* Set up the timeval structure for the timeout parameter */
	if(timo < 0)
		toptr = 0;
	else{
		toptr = &timeout;
		timeout.tv_sec = timo / 1000;
		timeout.tv_usec = (timo - timeout.tv_sec * 1000) * 1000;
	}
	rc = select(0, ip, op, &efds, toptr);
	if(rc <= 0)
		return rc;

	if(rc > 0) for(i=0; i<nfds; ++i){
		fd = fds[i].fd;
		if(fds[i].events & (POLLIN | POLLPRI) && FD_ISSET(fd, &ifds))
			fds[i].revents |= POLLIN;
		if(fds[i].events & POLLOUT && FD_ISSET(fd, &ofds))
			fds[i].revents |= POLLOUT;
		if(FD_ISSET(fd, &efds)){
			/* Some error was detected ... should be some way to know. */
			fds[i].revents |= POLLHUP;
		}
	}
	return rc;
}
