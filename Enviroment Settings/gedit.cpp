//Compile && gdb

#!/bin/sh

FILE=$GEDIT_CURRENT_DOCUMENT_NAME
OUT=${FILE%.*}

g++ -o $OUT $FILE -std=c++11 -g -Wall -Wextra && gnome-terminal --working-directory=$CURRENT_GEDIT_DOCUMENT_DIR -e "bash -c \"gdb ./$OUT; read \" "


//Compile && Open Terminal

//USE PROG.in if exists
#!/bin/sh


FILE=$GEDIT_CURRENT_DOCUMENT_NAME
OUT=${FILE%.*}

if [ -s $OUT.in ]; then
g++ -o $OUT $FILE -std=c++11 -O2 -Wall -Wextra && gnome-terminal --working-directory=$CURRENT_GEDIT_DOCUMENT_DIR -e "bash -c \"time ./$OUT < $OUT.in; read \" "
else
g++ -o $OUT $FILE -std=c++11 -O2 -Wall -Wextra && gnome-terminal --working-directory=$CURRENT_GEDIT_DOCUMENT_DIR -e "bash -c \"time ./$OUT; read \" "
fi

