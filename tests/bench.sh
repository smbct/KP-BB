for f in ../instances/*.dat
do
    echo $f >> benchBB
    echo $f >> benchGlpk
    ./../solver $f >> benchBB
    ./../glpkSolver $f >> benchGlpk
done
