for f in *.txt; do 
mv -- "$f" "${f%.txt}.cpp"
done
