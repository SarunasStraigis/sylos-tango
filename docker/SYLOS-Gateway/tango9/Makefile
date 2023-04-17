image:
	docker build -t tango9 .

container:
	docker run \
	-e TANGO_HOST=$(HOST):10000 \
	-e PYTHONPATH=/home/tangouser/ELI/tango-gateway-framework/src \
	--detach \
	--volume ~/ELI:/home/tangouser/ELI \
	--net host \
	--name tango9 \
	tango9
	echo "connect with 'docker exec -it tango9 bash'"

remove:
	docker rm -f tango9

clean:
	docker rm -f tango9
	docker image rm tango9
