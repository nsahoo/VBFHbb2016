#source $VO_CMS_SW_DIR/cmsset_default.sh
# shopt -s expand_aliases is needed if you want to use the alias 'cmsenv' created by $VO_CMS_SW_DIR/cmsset_default.sh instead of the less mnemonic eval `scramv1 runtime -sh`

source $VO_CMS_SW_DIR/cmsset_default.sh
source /swshare/psit3/etc/profile.d/cms_ui_env.sh  # for bash

export MYCMSENVDIR=/mnt/t3nfs01/data01/shome/nchernya/CMSSW_7_4_7/src/HiggsAnalysis/
cd $MYCMSENVDIR
eval `scramv1 runtime -sh`
shopt -s expand_aliases
cmsenv
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/dcap



export MYBATCHDIR=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/VBF_fit/bias/toys/$5
cd $MYBATCHDIR


echo combine -M GenerateOnly --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd ADDNLL_RECURSIVE=0 --X-rtd FITTER_NEW_CROSSING_ALGO --toysFrequentist -t $1 --expectSignal $2 --saveToys  --rMin=-7 --rMax=7 -n $3 -s -1  $4
 
combine -M GenerateOnly --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd ADDNLL_RECURSIVE=0 --X-rtd FITTER_NEW_CROSSING_ALGO --toysFrequentist -t $1 --expectSignal $2 --saveToys  --rMin=-7 --rMax=7 -n $3 -s -1  $4


#$ -o /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs2/
#$ -e /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs2/

