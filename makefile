cc = gcc
flag = -c
output = -o
all = myshell.o  find_command.o  do_cmd.o  print_prompt.o  get_input.o  explain_input.o  
obj = myshell

$(obj):$(all)
	$(cc)  $^ $(output) $@   
	@mkdir obj
	@mv *.o ./obj

%.o:%.c
	@$(cc) $(flag)  $< $(output) $@ -w




.PHONY:clean
clean:
	@rm -rf obj
	@rm myshell
	@echo "del ok !"




