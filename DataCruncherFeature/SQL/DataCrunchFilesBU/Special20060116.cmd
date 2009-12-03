e:
cd \datacrunchfiles
del LineCount.txt
del *.csv

call DTSToCSV DataCrunchTeacherQuality 2005 01
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa01.csv
call DTSToCSV DataCrunchTeacherQuality 2005 02
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa02.csv
call DTSToCSV DataCrunchTeacherQuality 2005 03
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa03.csv
call DTSToCSV DataCrunchTeacherQuality 2005 04
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa04.csv
call DTSToCSV DataCrunchTeacherQuality 2005 05
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa05.csv
call DTSToCSV DataCrunchTeacherQuality 2005 06
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa06.csv
call DTSToCSV DataCrunchTeacherQuality 2005 07
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa07.csv
call DTSToCSV DataCrunchTeacherQuality 2005 08
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa08.csv
call DTSToCSV DataCrunchTeacherQuality 2005 09
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa09.csv
call DTSToCSV DataCrunchTeacherQuality 2005 10
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa10.csv
call DTSToCSV DataCrunchTeacherQuality 2005 11
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa11.csv
call DTSToCSV DataCrunchTeacherQuality 2005 12
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2005_cesa12.csv

for %%z in (*.csv) do wc -l %%z | sort >> LineCount.txt
type LineCount.txt
