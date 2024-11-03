#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    allowed_functions.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oruban <oruban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/03 14:45:11 by oruban            #+#    #+#              #
#    Updated: 2024/11/03 14:45:12 by oruban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Generate the list of symbols in the executable
nm -C ./cub3d > symbols.txt

# Filter the undefined symbols
grep ' U ' symbols.txt > undefined_symbols.txt

# Generate the list of symbols in libft.a
nm -C libft/libft.a > libft_symbols.txt

# Filter the defined symbols in libft.a
grep ' T ' libft_symbols.txt > libft_defined_symbols.txt

# List of allowed external functions
allowed_functions=(
    "open" "close" "read" "write" "printf" "malloc" "free" "perror"
    "strerror" "exit" "gettimeofday" "sin" "cos" "tan" "asin" "acos"
    "atan" "atan2" "sinh" "cosh" "tanh" "exp" "log" "log10" "pow"
    "sqrt" "ceil" "floor" "fabs" "ldexp" "frexp" "modf" "fmod"
)

# Check each undefined symbol against the list of allowed functions
echo "External Functions Used (excluding libft):"
while read -r symbol; do
    func=$(echo "$symbol" | awk '{print $2}')
    if [[ " ${allowed_functions[@]} " =~ " ${func} " ]]; then
        echo "$func"
    elif ! grep -q " T $func" libft_defined_symbols.txt; then
        echo "$func"
    fi
done < undefined_symbols.txt