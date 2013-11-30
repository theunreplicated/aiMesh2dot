Wenns jemand verwenden will(was ich nicht glaube):
Verwendung: 
Debug\aiMesh2dot.exe datei_3d_modell.3ds ../../pfad_zur_dot_datei_in_die_geschrieben_werden_soll

falls das nicht gehen soll(tja,man weiß ja nie;-))
Pfade im Programm ändern,es sind glaub ich die 2 ersten Variablen im main

Und dann
.\dot.exe -T png graph.dot -o graph.png

Build(VS2010):
1.assimp als dependency hinzufügen(das gibts in den project properties(INclude dirs,lib dirs,additional include blub...))

Codequalität:sehr schlecht