
#ifndef Ch_D3D9_ModelCom_h
#define Ch_D3D9_ModelCom_h


typedef class ChModelComponent9 :public ChCpp::BaseComponent
{
public:

	virtual void SetModel(const std::string& _ModelName);

	inline ChPtr::Shared<ChMesh::BaseMesh9> InsModel() { return Model; }

	void Draw3D()override;

protected:

	ChPtr::Shared<ChMesh::BaseMesh9>Model = nullptr;

	void DIvidePathToName(
		std::string& _Path
		, std::string& _Name
		,const std::string& _FullPathName);

}ChModelCom9;

///////////////////////////////////////////////////////////////////////////////////

typedef class ChMModelComponent9 :public ChModelCom9
{
public:

	void SetModel(const std::string& _ModelName)override;

protected:

}ChMModelCom9;

///////////////////////////////////////////////////////////////////////////////////

typedef class ChSkinMeshModelComponent9 :public ChModelCom9
{
public:

	void SetModel(const std::string& _ModelName)override;

	ChPtr::Shared<ChMesh::SkinMesh9> GetSkinModel();

	void Update()override;

private:

}ChSkModelCom9;

///////////////////////////////////////////////////////////////////////////////////

typedef class ChMSkinMeshModelComponent9 :public ChSkModelCom9
{
public:

	void SetModel(const std::string& _ModelName)override;

private:

}ChMSkModelCom9;


#endif
