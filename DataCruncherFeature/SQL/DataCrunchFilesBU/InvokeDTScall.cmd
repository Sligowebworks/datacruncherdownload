del LineCount.txt

call DTScall.cmd

for %%z in (*.csv) do wc -l %%z | sort >> LineCount.txt
type LineCount.txt
