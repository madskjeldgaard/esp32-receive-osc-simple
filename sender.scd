(
// Target IP. Change the IP address accordingly
~ip = "10.0.0.11";
~port = 8888;
t = NetAddr.new(~ip, ~port);

)

// Turn led on
t.sendMsg("/led", 1)

// Turn led off
t.sendMsg("/led", 0)

// Or do it with a pattern
(

Pbind(
	\dur, Prand([0.25, 0.125, 0.5, 0.0125, 0.025], inf), 
	\led, Pxrand([1,0],inf),
	\play, Pfunc({|ev| t.sendMsg("/led", ev[\led])}),
).play

)
