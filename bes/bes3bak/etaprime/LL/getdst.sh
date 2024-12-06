dir="/besfs5/groups/ucas/lipr/7.0.6/samples/GenericMC"

energy=(4600 4612 4640 4660 4680 4700)
# energy2=(4600 4612 4626 4640 4660 4680 4700)

for i_e in ${energy[@]}
do
    find "$dir/${i_e}" -name "*.dst" > "${i_e}/${i_e}LLdst" &
done

find "$dir/4626" -name "*.dst" > "4620/4620LLdst" 