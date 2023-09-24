CLIENT = client
SERVER = server

defalt: $(CLIENT) $(SERVER)

.PHONY: $(CLIENT)
$(CLIENT):
	make -C $(CLIENT)

.PHONY: $(SERVER)
$(SERVER):
	make -C $(SERVER)

clean:
	make clean -C $(CLIENT)
	make clean -C $(SERVER)
