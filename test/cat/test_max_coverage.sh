#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"VAR test/cat/test_case_cat.txt"
)

declare -a extra=(
"-s test/cat/test_1_cat.txt"
"-b -e -n -s -t -v test/cat/test_1_cat.txt"
"-t test/cat/test_3_cat.txt"
"-n test/cat/test_2_cat.txt"
"no_file.txt"
"-n -b test/cat/test_1_cat.txt"
"-s -n -e test/cat/test_4_cat.txt"
"test/cat/test_1_cat.txt -n"
"-n test/cat/test_1_cat.txt"
"-n test/cat/test_1_cat.txt test/cat/test_2_cat.txt"
"-v test/cat/test_5_cat.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./gcat $t > test_cat.log
    cat $t > test_sys_cat.log
    DIFF_RES="$(diff -s test_cat.log test_sys_cat.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_cat.log and test_sys_cat.log are identical" ]
    then
      (( SUCCESS++ ))
        echo -e "$FAIL/$SUCCESS/$COUNTER\033[32m успех cat $t\033[0m"
    else
      (( FAIL++ ))
        echo -e "$FAIL/$SUCCESS/$COUNTER\033[31m ошибка cat $t\033[0m"
    fi
    rm test_cat.log test_sys_cat.log
}


for i in "${extra[@]}"
do
    var="-"
    testing $i
done


for var1 in b e n s t v
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done


for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done


for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        for var3 in b e n s t v
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done


for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        for var3 in b e n s t v
        do
            for var4 in b e n s t v
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        testing $i
                    done
                fi
            done
        done
    done
done

echo "ОШИБКИ: $FAIL"
echo "УСПЕШНО: $SUCCESS"
echo "ВСЕГО: $COUNTER"
