# Custom message in green text when launching the terminal
echo -e "Launch \e[32mcmake ..\e[0m"
echo -e "After this you can:"
echo -e "\e[32mmake code\e[0m Builds the firmware."
echo -e "\e[32mmake test\e[0m Runs unit tests."
echo -e "\e[32mmake dynamic\e[0m Runs dynamic code analysis."
echo -e "\e[32mmake static\e[0m Runs static code analysis."
echo -e "\e[32cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j23 && make test -j23 && make coverage\e[0m Runs code coverage analysis."
echo -e "\e[32mmake docs\e[0m Runs coverage for missing documentation.\e[0m"

alias ll='ls -l --color=always'

