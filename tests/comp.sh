for f in ../instances/pisinger/knapPI_1_10000_10000/*.dat
do
    timeout 5 ./../solver $f >> knapPI_1_10000_10000
done

for f in ../instances/pisinger/knapPI_3_200_100000/*.dat
do
    timeout 5 ./../solver $f >> knapPI_3_200_100000
done

for f in ../instances/pisinger/knapPI_11_50_1000/*.dat
do
    timeout 5 ./../solver $f >> knapPI_11_50_1000
done
