#include <xml_para.h>

using namespace std;

int writeXmlFile(int _xml_para[2][5])
{
  TiXmlDocument *writeDoc = new TiXmlDocument;
  
  //文档格式声明
  TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "UTF-8", "yes");
  writeDoc->LinkEndChild(decl); 

  int n = 2;

  TiXmlElement *RootElement = new TiXmlElement("Info");//根元素
  RootElement->SetAttribute("num", n); //属性
  writeDoc->LinkEndChild(RootElement);
  
  for(int i=0; i<n; i++)
  {
    if(!i)//img
    {
      TiXmlElement *StuElement = new TiXmlElement("camera");
      //设置属性
      StuElement->SetAttribute("to","img");
      RootElement->LinkEndChild(StuElement);//父节点写入文档

      char time_interval_img[3];
      sprintf(time_interval_img,"%d",_xml_para[0][0]);  
      TiXmlElement *nameElement = new TiXmlElement("time_interval");
      StuElement->LinkEndChild(nameElement);

      TiXmlText *nameContent = new TiXmlText(time_interval_img);
      nameElement->LinkEndChild(nameContent);
      
      char img_id[3];
      sprintf(img_id,"%d",_xml_para[0][1]);  
      TiXmlElement *scoreElement = new TiXmlElement("id");
      StuElement->LinkEndChild(scoreElement);

      TiXmlText *scoreContent = new TiXmlText(img_id);
      scoreElement->LinkEndChild(scoreContent);
    }
    else
    {
      TiXmlElement *StuElement = new TiXmlElement("camera");
      //设置属性
      StuElement->SetAttribute("to","vid");
      RootElement->LinkEndChild(StuElement);//父节点写入文档

      char time_interval_vid[3];
      sprintf(time_interval_vid,"%d",_xml_para[1][0]);
      TiXmlElement *nameElement = new TiXmlElement("time_interval");
      StuElement->LinkEndChild(nameElement);

      TiXmlText *nameContent = new TiXmlText(time_interval_vid);
      nameElement->LinkEndChild(nameContent);
      
      char vid_id[3];
      sprintf(vid_id,"%d",_xml_para[1][1]); 
      TiXmlElement *scoreElement = new TiXmlElement("id");
      StuElement->LinkEndChild(scoreElement);

      TiXmlText *scoreContent = new TiXmlText(vid_id);
      scoreElement->LinkEndChild(scoreContent);
      
      char fps[3];
      sprintf(fps,"%d",_xml_para[1][2]);
      TiXmlElement *cityElement = new TiXmlElement("fps");
      StuElement->LinkEndChild(cityElement);

      TiXmlText *cityContent = new TiXmlText(fps);
      cityElement->LinkEndChild(cityContent);
      
      char fps_enable[3];
      sprintf(fps_enable,"%d",_xml_para[1][3]);
      TiXmlElement *fpsenElement = new TiXmlElement("fps_enable");
      StuElement->LinkEndChild(fpsenElement);

      TiXmlText *fpsenContent = new TiXmlText(fps_enable);
      fpsenElement->LinkEndChild(fpsenContent);
      
      char vid_duration[3];
      sprintf(vid_duration,"%d",_xml_para[1][4]);
      TiXmlElement *vid_durationElement = new TiXmlElement("vid_duration");
      StuElement->LinkEndChild(vid_durationElement);

      TiXmlText *vid_durationContent = new TiXmlText(vid_duration);
      vid_durationElement->LinkEndChild(vid_durationContent);
      }    
	  
  }
  
  writeDoc->SaveFile("../../camera_info.xml");
  delete writeDoc;
  
  return 1;
}

int readXmlFile(int _xml_para[2][5])
{
  TiXmlDocument mydoc("../../camera_info.xml");
  bool loadOk=mydoc.LoadFile();
  int i = 0, j = 0;
  if(!loadOk)
  {
      return -1;

  }

  TiXmlElement *RootElement=mydoc.RootElement();	//根元素, Info
  
  TiXmlElement *pEle=RootElement;
  cout << "---------------------------------" << endl;
  cout << "Parameters in the camera_info.xml" << endl;
  //遍历该结点
  for(TiXmlElement *StuElement = pEle->FirstChildElement();
	  StuElement != NULL;
	  StuElement = StuElement->NextSiblingElement())
  {
	  cout<<endl;
	  // StuElement->Value() 节点名称
	  cout<< StuElement->Value() <<" ";
	  TiXmlAttribute *pAttr=StuElement->FirstAttribute();//第一个属性
	  

	  while( NULL != pAttr) 
	  {
		  cout<<pAttr->Name()<<":"<<pAttr->Value()<<" ";
		  pAttr=pAttr->Next();
	  }
	  cout<<endl;
	  cout<<endl;
	  
	  //输出子元素的值
	  for(TiXmlElement *sonElement=StuElement->FirstChildElement();
	  sonElement;
	  sonElement=sonElement->NextSiblingElement())
	  {
		  _xml_para[i][j] = atoi(sonElement->FirstChild()->Value());
		  
		  switch(j)
		  {
		    case 0: cout<<"时间间隔（s）:  ";break;
		    case 1: cout<<"已保存编号:     ";break;
		    case 2: cout<<"fps:            ";break;
		    case 3: cout<<"自动获取fps:    ";break;
		    case 4: cout<<"视频截取长度(s)：  ";break;
		    default: break;
		  }
		  
		  j++;
		  
		  cout<<sonElement->FirstChild()->Value()<<endl;
	  }
	  i++;
	  j = 0;
  }
  cout<<endl;
  cout << "---------------------------------" << endl;
  cout<<endl;
  return 1;
}
