// aiMesh2dot.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <sstream>
#include <string>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>  
#include <fstream>
#include <Windows.h>
using namespace std;
class Manager{
private:
		 string result;
public:

	 void add(string toadd){result=result+toadd; };
	
	string out(){return result;};
};
class aiHandler{
private:Manager * manager_ref;//const aiScene* scene;
public:aiHandler(Manager *  m,std::string filename){
	   Assimp::Importer importer;
manager_ref=m;
    const aiScene* scene = importer.ReadFile(filename, 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);
	
	if(scene->HasMeshes()){
		for(int i=0;i<scene->mNumMeshes;i++){

			aiRender(scene->mMeshes[0],i);
		
		}	
	}
	};

	void aiRender(aiMesh *mesh,int index){
		std::string str,str2;
		str=mesh->mName.C_Str();
		str2="Mesh:"+str;
		stringstream ik;
		ik<<index;
		string meshname="Mesh"+ik.str();
		manager_ref->add(meshname+"[label=\""+str2+"\"];");	
		if(mesh->HasPositions()){
			string Vertices_name="Vertices";
			manager_ref->add(meshname+"->"+Vertices_name+";");
			stringstream mvert;
			mvert<<mesh->mNumVertices;
			manager_ref->add(meshname+"->"+"NumVertices"+mvert.str()+";");
			for(int i=0;i<mesh->mNumVertices;i++){
				stringstream blub;
				blub<<i;
				string cname=meshname+Vertices_name+blub.str();
				manager_ref->add(cname+"[label=\"");
				
				aiRender(mesh->mVertices[i]);
				manager_ref->add("\"];");
				manager_ref->add(Vertices_name+"->"+cname+";");
			}}
		if(mesh->HasFaces()){
			
			string faces_name="Faces";
			manager_ref->add(meshname+"->"+faces_name+";");
			stringstream numfaces;
			numfaces<<mesh->mNumFaces;
			manager_ref->add(faces_name+"->numFaces"+numfaces.str()+";");
				aiRender(mesh->mFaces,faces_name);
				for(int i=0;i<mesh->mNumFaces;i++){
				aiFace* facess=&mesh->mFaces[i];
				stringstream fdsdas;
				fdsdas<<i;
				aiRender(facess,faces_name+"->Face"+fdsdas.str());
			}
		};
		
	   };

	 void aiRender(aiFace * face,string faces_name){

stringstream s2;
s2<<face->mNumIndices;

//manager_ref->add("indices");
manager_ref->add(faces_name+"->"+"numIndices"+s2.str()+";");

string indices_name="Indices";
for(int i=0;i<face->mNumIndices;i++){
	stringstream ind;
	ind<<face->mIndices[i];
	manager_ref->add(faces_name+"->"+indices_name+"->"+ind.str()+";");

}

	};
	 void aiRender(aiVector3D pos){
		 stringstream x;
		 x<<pos.x;
		 stringstream y;
		 y<<pos.y;
		 stringstream z;
		 z<<pos.z;//TODO:in funktion auslagern,nix copy n paste,das geht gaaaar net

		 manager_ref->add(x.str()+","+y.str()+","+z.str());
	 };
};
int main(int argc, char* argv[])
{
	
	string openfile="cube.3DS";
	string dotpath="../../../../graphviz/graph.dot";

	if(argv[1]&&argc>=2){
	openfile=argv[1];
	}
	if(argv[2]&&argc>=3){//cout<<"arg3";
	dotpath=argv[2];
	
	}
	Manager * m= new Manager();
	aiHandler * handle= new aiHandler(m,openfile);
	std::cout<<m->out();
	
		
	ofstream fstream;
	fstream.open(dotpath);//usage:dot.exe -T png [[dotpath]] -o [[outputfile]] ([[ weglassen)
	fstream<<"digraph Graph1{"<<m->out()<<"}";
	fstream.close();

	std::getchar();
	return 0;
}

