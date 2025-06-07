#!/bin/bash

container_name="schedule_container"
image_name="schedule"

cd ..

sudo docker build -t $image_name .

if [ "$(sudo docker ps -a -q -f name=$container_name)" ]; then
    sudo docker stop $container_name
    sudo docker rm $container_name
fi

sudo docker run --name $container_name -it $image_name /bin/bash