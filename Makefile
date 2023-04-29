SRC = main.cpp server.cpp request.cpp client.cpp ./parsing/parse_post.cpp ./config/config_file.cpp response.cpp ./response/get_method.cpp ./response/get_utils.cpp ./response/delete_mothod.cpp 
CFLAGS =  -fsanitize=address #-std=c++98
CPP = c++
NAME = server
CLIENT = client

all: $(NAME)

$(NAME): $(SRC)
	@$(CPP) $(CFLAGS) $(SRC) -o $(NAME) 

clean:

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(CLIENT)


re : fclean all

client: client.cpp
	@$(CPP) $(CFLAGS) client.cpp -o client
	

.PHONY: all clean fclean re