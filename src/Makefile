
CC = gcc
CFLAG = -g -o
COFLAG = -g -c

TAGOBJ = getcodesfile getcurrentinfo regetcodedata gethistinfo getcurrentandhist

LINKLIB = -lpthread

INCLDIR = $(HOME)/incl

all:$(TAGOBJ)
	ctags *.c $(INCLDIR)/*.h

getcodesfile:getcodesfile.o 
	$(CC) $(CFLAG) $@ $^

getcurrentinfo:getcurrentinfo.o getsharesinfotools.o sharethreadtool.o
	$(CC) $(CFLAG) $@ $^ $(LINKLIB)

gethistinfo:gethistinfo.o getsharesinfotools.o sharethreadtool.o
	$(CC) $(CFLAG) $@ $^ $(LINKLIB)

getcurrentandhist:getcurrentandhist.o getsharesinfotools.o sharethreadtool.o
	$(CC) $(CFLAG) $@ $^ $(LINKLIB)

regetcodedata:regetcodedata.o getsharesinfotools.o sharethreadtool.o
	$(CC) $(CFLAG) $@ $^ $(LINKLIB)

.c.o:
	$(CC) $(COFLAG) -I$(INCLDIR) $<
