e:
cd \datacrunchfiles
del LineCount.txt
del *.csv
rem pause
call DTSToCSV DataCrunchTeacherQuality 2003 01
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa01.csv
call DTSToCSV DataCrunchTeacherQuality 2003 02
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa02.csv
call DTSToCSV DataCrunchTeacherQuality 2003 03
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa03.csv
call DTSToCSV DataCrunchTeacherQuality 2003 04
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa04.csv
call DTSToCSV DataCrunchTeacherQuality 2003 05
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa05.csv
call DTSToCSV DataCrunchTeacherQuality 2003 06
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa06.csv
call DTSToCSV DataCrunchTeacherQuality 2003 07
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa07.csv
call DTSToCSV DataCrunchTeacherQuality 2003 08
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa08.csv
call DTSToCSV DataCrunchTeacherQuality 2003 09
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa09.csv
call DTSToCSV DataCrunchTeacherQuality 2003 10
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa10.csv
call DTSToCSV DataCrunchTeacherQuality 2003 11
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa11.csv
call DTSToCSV DataCrunchTeacherQuality 2003 12
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2003_cesa12.csv
call DTSToCSV DataCrunchTeacherQuality 2004 01
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa01.csv
call DTSToCSV DataCrunchTeacherQuality 2004 02
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa02.csv
call DTSToCSV DataCrunchTeacherQuality 2004 03
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa03.csv
call DTSToCSV DataCrunchTeacherQuality 2004 04
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa04.csv
call DTSToCSV DataCrunchTeacherQuality 2004 05
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa05.csv
call DTSToCSV DataCrunchTeacherQuality 2004 06
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa06.csv
call DTSToCSV DataCrunchTeacherQuality 2004 07
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa07.csv
call DTSToCSV DataCrunchTeacherQuality 2004 08
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa08.csv
call DTSToCSV DataCrunchTeacherQuality 2004 09
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa09.csv
call DTSToCSV DataCrunchTeacherQuality 2004 10
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa10.csv
call DTSToCSV DataCrunchTeacherQuality 2004 11
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa11.csv
call DTSToCSV DataCrunchTeacherQuality 2004 12
ren TempFileOutput.csv what_are_the_qualifications_of_teachers_2004_cesa12.csv

for %%z in (*.csv) do wc -l %%z | sort >> LineCount.txt
type LineCount.txt
