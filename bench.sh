for f in instances/*.dat
do
    echo $f >> tests/benchBB
    echo $f >> tests/benchGlpk
    ./main $f >> tests/benchBB
    ./glpkSolver $f >> tests/benchGlpk
done
