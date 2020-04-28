sudo apt-get install git
sudo apt-get install vim-gui-common 
sudo apt-get install vim-runtime
sudo apt-get install bluetooth bluez-utils blueman
sudo apt-get install ssh
sudo apt-get install openssh-server
sudo sudo apt-get install vsftpd
FILE="./bashrc"
sudo echo "export VISUAL=\"vim\"" > $FILE
sudo echo "export EDITOR=\"$VISUAL\""> $FILE
sudo cp ~/20200428success/vimrc ~/.vimrc
sudo update-rc.d ssh defaults
sudo apt-get install tmux
