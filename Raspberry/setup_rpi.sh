### HOSTNAME ###
echo liceti-robotica > /etc/hostname
/etc/init.d/hostname.sh start
### UPDATE ### 
APT_SOURCES=("deb http://archive.raspbian.org/raspbian testing main contrib non-free" "deb-src http://archive.raspbian.org/raspbian testing main contrib non-free")
echo "# repository di upgrade" > /etc/apt/sources.list
for text in "${APT_SOURCES[@]}"
do
	echo $text >> /etc/apt/sources.list
done
wget https://archive.raspbian.org/raspbian.public.key -O - | apt-key add -
apt-get update && apt-get dist-upgrade
### FIRMWARE UPDATE ###
apt-get install rpi-update
BRANCH=next rpi-update