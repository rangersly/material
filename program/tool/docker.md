安装docker
	sudo apt-get install docker-compose

配置/etc/docker/daemon.json
	
{
	"registry-mirrors":
	[
        "https://dockerproxy.com",
        "https://docker.mirrors.ustc.edu.cn",
        "https://docker.nju.edu.cn"
    ]  
}

docker ps 		#查看所有运行容器
docker ps -a	#全部

docker stop [ID / NAME]		#停止某容器

docker start [ID / NAME]	#启动和删除容器
docker rm [ID / NAME]

docker pull 仓库名/镜像名

docker save  [ID] > xxx.tar	#导出为tar文件
docker load < xxx.tar		#导入tar为镜像

docker commit [ID] [镜像名]	#容器保存为镜像

docker image ls				#查看本地所有镜像
docker rmi [ID / NAME]		#删除镜像

docker exec -it [ID / NAME] bash	#操作容器
