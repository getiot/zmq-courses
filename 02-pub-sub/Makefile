all: publisher subscriber
%: %.c
	gcc -I../inc/ $^ -o $@ -lzmq

clean:
	rm publisher subscriber