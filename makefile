GCC = gcc
SOURCE = ./BuildMessage/*.c ./CheckSum/*.c ./FileOperation/*.c ./FileUpload/*.c ./MemoryMng/*.c ./ModemResponse/*.c ./*.c
CFLAG = -W -I ./BuildMessage -I ./ModemResponse -I ./CheckSum -I./Common -I ./FileOperation -I ./FileUpload -I ./MemoryMng 
OUT = -o ./Build/FileUpload
CLEAR = del -f $(OUT)

make :		$(SOURCE)
			$(GCC) $(CFLAG) $(SOURCE) $(OUT)

clean : 
		$(CLEAR)
