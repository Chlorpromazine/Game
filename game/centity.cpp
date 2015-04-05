#include <iostream>
#include "CEntity.h"
 using namespace std;

std::vector<CEntity*> CEntity::EntityList;

//keep track of the number of entitiesi n the area
static unsigned int entityNumberInArea = 0;

/*
namespace std {

  template <>
  struct hash<CEntity::commonEntities>
  {
    std::size_t operator()(const CEntity::commonEntities& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return ((hash<int>()(k.height)
               ^ (hash<int>()(k.frames) << 1)) >> 1)
               ^ (hash<int>()(k.width) << 1);
    }
  };

}
*/

std::unordered_map<std::string, CEntity::commonEntities> CEntity::surfEntityList;

CEntity CEntity:: EntityControl;

CEntity::CEntity() 
{
    Surf_Entity = NULL;
 
    xDraw = yDraw = xPos = yPos = 100.0f;
 
    Width = Height = 0;
 
    AnimState = 0;

	currentHP = maxHP = 0;

	faceDirection = rand()%8+1; //random facing direction
}
 
CEntity::~CEntity() {
}
 
bool CEntity::OnLoad(char* File, int Width, int Height, int MaxFrames, int entityType, int locX) 
{
	//Todo: set framerate based on entity
    if((Surf_Entity = CSurface::OnLoad(File)) == NULL) 
	{
        return false;
    }
 
    CSurface::Transparent(Surf_Entity, 255, 255, 255);
 
    this->Width = Width;
    this->Height = Height;
	
    Anim_Control.MaxFrames = MaxFrames;
	Anim_Control.SetFrameRate(500);
	AnimState = entityType;
	startX = locX;
    return true;
}
 
void CEntity::OnLoop() {
	Anim_Control.OnAnimate();

}
 
void CEntity::OnRender(SDL_Surface* Surf_Display) 
{
    if(Surf_Entity == NULL || Surf_Display == NULL) return;
	
	//todo: remove startX, replace with frame
	CSurface::OnDraw(Surf_Display, Surf_Entity, (int)xDraw - ((Width - widthCol) / 2), (int)yDraw - ((Height - heightCol) / 2), 
					Anim_Control.GetCurrentFrame() * (startX+Width), faceDirection* Height, Width, Height);
}
 
void CEntity::OnCleanup() {
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }
 
    Surf_Entity = NULL;
}

void CEntity::moveX(float x)
{
	this->xDraw += x;
	this->xPos += x;

}

void CEntity::moveY(float y)
{
	this->yDraw += y;
	this->yPos += y;
}

void CEntity::newEntity(int x,int y,string entityName)
{	
	commonEntities newEntity;
	CEntity *tempEntity = new CEntity();

	unordered_map<string,commonEntities>::const_iterator got = surfEntityList.find (entityName);

	//if the images are already loaded, don't load it again.
	if ( got == surfEntityList.end() )
	{
		cout << "Error: surface not found" << endl;
		return;
	}

	tempEntity->Surf_Entity = got->second.Surface;
	tempEntity->Anim_Control.MaxFrames = got->second.frames;

	tempEntity->xDraw = (float)x;
	tempEntity->xPos = (float)x;
	tempEntity->yDraw = (float)y;
	tempEntity->yPos = (float)y;

	tempEntity->AnimState = got->second.entityNumber;
	tempEntity->startX = got->second.startX;
	tempEntity->Width = got->second.width;
	tempEntity->Height = got->second.height;
	tempEntity->heightCol = got->second.heightCollision;
	tempEntity->widthCol = got->second.widthCollision;
	tempEntity->currentHP = tempEntity->maxHP = 100;


	EntityList.push_back(tempEntity);

	AI::AIControl.resizeVector(1);
	
}

void CEntity::substractHP(float value,int entityNumber)
{
	EntityList[entityNumber]->currentHP -= round(value);
}

void CEntity::checkIfDead(int entityNumber)
{
	//if the entity is dead, remove if from the entity list
	if (EntityList[entityNumber]->currentHP <= 0)
	{
		delete EntityList[entityNumber];
		EntityList.erase(EntityList.begin() + entityNumber);
		AI::AIControl.resizeVector(-1);
	}
}

//load the information of all the entities in an area
void CEntity::loadEntityImages(char* file)
{
	string data;
	ifstream info;
	info.open("images\\entityInfo.txt");
	
	int entNumber = 0;
	string name[] = {"path","entityName","height","width","heightCollision","widthCollision","animationMaxFrame","startX"};

	while(!info.eof()) 
    {
		commonEntities newEntity;
		//go through all the information of one entity
		for (int i = 0; i < sizeof(name) / sizeof(name[0]); i++)
		{
			getline(info, data);
			//if it's a comment or blank, skip the line
			if (data == "" || data[0] == '#')
			{
				i--;
				continue;
			}

			vector<string> splitData = split(data, '=');

			//grab the information
			if (splitData[0] == name[0])	newEntity.path = splitData[1];
			else if (splitData[0] == name[1]) newEntity.entityName = splitData[1];
			else if (splitData[0] == name[2]) newEntity.height = atoi(splitData[1].c_str());
			else if (splitData[0] == name[3]) newEntity.width = atoi(splitData[1].c_str());
			else if (splitData[0] == name[4]) newEntity.heightCollision = atoi(splitData[1].c_str());
			else if (splitData[0] == name[5]) newEntity.widthCollision = atoi(splitData[1].c_str());
			else if (splitData[0] == name[6])
			{
				newEntity.frames = atoi(splitData[1].c_str());
				newEntity.entityNumber = entNumber++;
			}
			else if (splitData[0] == name[7])
			{
				newEntity.frames = atoi(splitData[1].c_str());
				newEntity.startX = atoi(splitData[1].c_str());

			}

			else cout << "Error in entity file" << endl;
		}
		newEntity.Surface = CSurface::OnLoad(&newEntity.path[0]);
		CSurface::Transparent(newEntity.Surface, 255, 255, 255);
		surfEntityList[newEntity.entityName] = newEntity;
	}
     
	info.close();

}

void CEntity::loadCurrentSurface(char* file)
{
	if((Surf_Entity = CSurface::OnLoad(file)) == NULL) 
	{
        cout << "Error, can't load selected surface" << endl;
    }
}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

void CEntity::setFrame(int i,int frame)
{
	EntityList[i]->Anim_Control.SetCurrentFrame(frame);
}

void CEntity::setMaxFrame(int i, int max)
{
	EntityList[i]->Anim_Control.MaxFrames = max;
}

void CEntity::setStartFrame(int i, int frame)
{
	EntityList[i]->startX = frame * EntityList[i]->Width;

}