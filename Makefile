vector.o: vector.c lpc1114.h
	gcc-arm -mcpu=cortex-m0 -c -g vector.c
reset.o: reset.c lpc1114.h
	gcc-arm -mcpu=cortex-m0 -c -g reset.c
stepper.o: stepper.c lpc1114.h
	gcc-arm -c -g stepper.c
hall.o: hall.c lpc1114.h main.h
	gcc-arm -c -g hall.c
ssd1306.o: ssd1306.c lpc1114.h
	gcc-arm -mcpu=cortex-m0 -c -g ssd1306.c
front_derailer.o: front_derailer.c lpc1114.h
	gcc-arm -mcpu=cortex-m0 -c -g front_derailer.c

libos.a: vector.o reset.o 
	ar-arm crs libos.a vector.o reset.o

lcd: ssd1306.o libos.a
	ld-arm -o lcd -T lpc1114.ld libos.a ssd1306.o
stepper: stepper.o libos.a 
	ld-arm -o stepper -T lpc1114.ld libos.a stepper.o
adservo: libos.a lpc1114.ld hall.o 
	ld-arm -o adservo -T lpc1114.ld libos.a hall.o  
f_derail: front_derailer.o libos.a
	ld-arm -o f_derail -T lpc1114.ld libos.a front_derailer.o


main: libos.a front_derailer.o ssd1306.o hall.o stepper.o
	ld-arm -o main -T lpc1114.ld libos.a front_derailer.o ssd1306.o hall.o stepper.o
run: main
	openocd -f interface/stlink-v2.cfg -f target/lpc11xx.cfg -c'program main verify reset exit'


lcd_ocd: lcd	
	openocd -f interface/stlink-v2.cfg -f target/lpc11xx.cfg -c'program lcd verify reset exit'
ocd: adservo
	openocd -f interface/stlink-v2.cfg -f target/lpc11xx.cfg -c'program adservo verify reset exit'
step_ocd: stepper
	openocd -f interface/stlink-v2.cfg -f target/lpc11xx.cfg -c'program stepper verify reset exit'
front_ocd: f_derail
	openocd -f interface/stlink-v2.cfg -f target/lpc11xx.cfg -c'program f_derail verify reset exit'
gdb: 
	openocd -f interface/stlink-v2.cfg -f target/lpc11xx.cfg -c'gdb_port 3333; gdb_memory_map disable'


clean: 
	rm hall.o reset.o vector.o ssd1306.o stepper.o front_derailer.o libos.a adservo lcd stepper f_derail main.o main
	clear
