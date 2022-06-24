all: ventilator worker sink
%: %.c
	gcc -I../inc/ $^ -o $@ -lzmq

clean:
	rm ventilator worker sink