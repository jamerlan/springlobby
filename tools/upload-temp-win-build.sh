#! /bin/bash

set -e
cd $(dirname $0)/../$1
pwd

/usr/i586-mingw32msvc/bin/strip springlobby.exe

if [ x$2 == x ]; then
	filename=sl_master.zip
else
	filename=sl_${2}.zip
fi

zip -9 -u ${filename} springlobby.exe

scp -p ${filename} springlobby:/usr/local/www/springlobby.info/temp/builds/${filename}
ssh springlobby chmod g+r /usr/local/www/springlobby.info/temp/builds/${filename}

echo "http://springlobby.info/temp/builds/${filename}"
