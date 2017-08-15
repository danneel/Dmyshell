cc = gcc
flag = -c
output = -o
all = myls.o display_normal_file.o handle_param.o myerror.o display_dir.o 
obj = myls

$(obj):$(all)
	$(cc) $^ $(output) $@ -w -g
	@mkdir obj
	@mv *.o ./obj

%.o:%.c
	$(cc) $(flag) $< $(output) $@ -w




.PHONY:clean
clean:
	@rm -rf obj
	@rm myls
	@echo "del ok !"
