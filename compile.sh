mygzstream=~/software/GZSTREAM/gzstream

check=`echo ${CPLUS_INCLUDE_PATH} | grep gzstream`

if [[ ! -n ${check} ]]; then
	if [[ -n ${mygzstream} ]]; then
		export CPLUS_INCLUDE_PATH=$mygzstream:${CPLUS_INCLUDE_PATH}
	else
		echo 
	        echo " Error!! gzstream not found in your CPLUS_INCLUDE_PATH"
		echo " Please add gzstream to your CPLUS_INCLUDE_PATH"
		echo "  or include the path in the mygzstream variable on line 1 of this script ($0) then 'source $0'" 
		echo
	fi
fi
make clean all

