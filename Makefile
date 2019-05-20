all:
	$(MAKE) -C Homework_1  $@
	$(MAKE)   -C Homework_2  $@
	$(MAKE)   -C Homework_3_5  $@
	$(MAKE)  -C Homework_4  $@
	$(MAKE)   -C Homework_6  $@
	$(MAKE)  -C Homework_7  $@

clean:
	$(MAKE) clean -C Homework_1  $@
	$(MAKE) clean  -C Homework_2  $@
	$(MAKE) clean  -C Homework_3_5  $@
	$(MAKE) clean -C Homework_4  $@
	$(MAKE) clean  -C Homework_6  $@
	$(MAKE) clean  -C Homework_7  $@
