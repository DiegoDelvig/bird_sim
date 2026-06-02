##
# bird_sim
#
# @file
# @version 0.1

main:
	gcc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o bird_sim
	./bird_sim


# end
