Efter att ha lyckats med en HashTabbel med seperate chaning testade jag lite olika förhollande på antal elemetn i en bucket och totalt antal elemnt i tabellen och jag fick alldrig bättre än när jag hade 0.5 vid ökning och 0.25 vid minskning av antal buckets

Intresant nog blev koden lite långsammare när jag lade till is_occupide i min struct för att mainkdoen skulle vara kompatibel med både Seperate chaining och lineare probing. Jick från 0.515s till 0.573s vilket sjlvkalrt är en liten skillnad men endå intresent. Beror troligtvis på att mainfunktionen får en extra sak att ta in i varge steg även om den inte används.

Förutom att det är logiskt cool med linear probing ser jag ingen anledning att använda det då Seperate chaning är nest intill lika snabbt när man hanterar indata i storleksordningen 5 milioner
