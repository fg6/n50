mygzstream=~/software/GZSTREAM/gzstream

check=`echo ${CPLUS_INCLUDE_PATH} | grep gzstream`
if [[ -n ${check} ]]; then
	echo gzstream found
else
        echo gzstream not found!
	export CPLUS_INCLUDE_PATH=$mygzstream:${CPLUS_INCLUDE_PATH}
fi
make clean all

