./rm_hook.sh

osName=libhook.so
hookPath=/etc/hook_watch

echo $hookPath/$osName > ld.so.preload
sudo rm $hookPath/$osName
sudo cp $osName $hookPath/
sudo cp ld.so.preload /etc/
