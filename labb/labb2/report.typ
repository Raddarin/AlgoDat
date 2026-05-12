Efter att ha lyckats med en HashTabbel med seperate chaning testade jag lite olika förhollande på antal elemetn i en bucket och totalt antal elemnt i tabellen och jag fick alldrig bättre än när jag hade 0.5 vid ökning och 0.25 vid minskning av antal buckets


Förutom att det är logiskt cool med linear probing ser jag ingen anledning att använda det då Seperate chaning är nest intill lika snabbt när man hanterar indata i storleksordningen 5 milioner




#align(center)[*Linear Probing*]
#table(
  columns: (1fr, 1fr),
  inset: 10pt,
  align: center + horizon,
  fill: (x, y) => if y == 0 { gray.lighten(50%) },
  stroke: 0.5pt + gray,
  [*$alpha$*], [*Time (s)*],
  [0.8], [0.775],
  [0.7], [0.825],
  [0.6], [0.525],
  [0.5], [0.525],
  [0.4], [3.385],
)
#align(center)[*Quadratic probing*]
#table(
  columns: (1fr, 1fr),
  inset: 10pt,
  align: center + horizon,
  fill: (x, y) => if y == 0 { gray.lighten(50%) },
  stroke: 0.5pt + gray,
  [*$alpha$*], [*Time (s)*],
  [0.8], [--:--],
  [0.7], [0.534],
  [0.6], [0.526],
  [0.5], [0.526],
  [0.4], [0.527],
  [0.3], [0.572],
)

Vid $alpha$ = 0.8 funkar inte hashtabllen med quadratic proabing men för övrigt är skillanderna små vid olika $alpha$.

Intresant nog blev koden lite långsammare när jag lade till is_occupide i min struct för att mainkdoen skulle vara kompatibel med både Seperate chaining och lineare probing. Jick från 0.515s till 0.573s vilket sjlvkalrt är en liten skillnad men endå intresent. Beror troligtvis på att mainfunktionen får en extra sak att ta in i varge steg även om den inte används.

#pagebreak()
För att se skillanden testar jag både seperate chaning med den generella och inte generella mainkoden.

Alla tester körs 100 gånger och ett medlevärlde beräknas och size mellan 0.5 och 0.25.
#table(
  columns: (1fr, 1fr),
  inset: 10pt,
  align: center + horizon,
  fill: (x, y) => if y == 0 { gray.lighten(50%) },
  stroke: 0.5pt + gray,
  [*Hash method*], [*Time (s)*],
  [Seperate Chaning (Generell main-kod)], [0.523],
  [Seperate Chaning (Särskild main-kod)], [0.509],
  [Linear Probing], [0.500],
  [Quadratic Probing], [0.536],
  [Reference Python], table.cell(fill: red.lighten(90%))[1.685],
  [unorderd_map], table.cell(fill: green.lighten(90%))[0.376],
)




Jag tror att det som tar mest tid är att reehasha eftersom då måste den då måste sortera in alla ellement igen.


Med den binära modulus beräkningen kapar man en operation från varge indexberäkning och ger en tid på 0.477 s i genomsnitt.
