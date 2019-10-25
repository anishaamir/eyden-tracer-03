#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"

#include <fstream>

void CScene::ParseOBJ(const std::string& fileName)
{
	std::cout << "Parsing OBJFile : " << fileName << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));

	std::ifstream fileN(fileName);
	if(!fileN){
		std::cout << "Wrong Path!/Incorrect File Name!";
	}
	std::vector<Vec3f> vertices; 
	std::vector<int> fx, fy, fz; 
	int n = 0; 
	while(!fileN.eof()){
		char line;
		fileN >> line;
		if (line == 'v'){
			Vec3f vertex;
			for (int i=0; i<3; i++){ 
				fileN >> vertex[i];
				vertex[i] *= 100; 
			
			}
			vertices.push_back(vertex); 
		}
		else if (line == 'f'){
			int x, y, z;
			fileN >> x >> y >> z;
		
			fx.push_back(x);
			fy.push_back(y);
			fz.push_back(z);
			n++;
		}
	}
	for (int i =0; i < n ; i++){ 
		Add(std::make_shared<CPrimTriangle>(vertices[fx[i]-1],
			vertices[fy[i]-1], vertices[fz[i]-1], pShader));
	}

	std::cout << "Finished Parsing" << std::endl;
	fileN.close();
}

