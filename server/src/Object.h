#pragma once
#include "stdafx.h"
#include "Model.h"

#define DEFAULT_OBJECT_COLOR WHITE

/************************************************** [ TOP ROOTS ] **************************************************/

//////////////////////////////////////// [ Object ] ////////////////////////////////////////
class Object abstract {
protected:
	/* Rotation, Scaling, Pivot ���� ���� ��ġ */
	glm::vec3 mPosition = glm::vec3(0,0,0);

	/* ����, �ٶ󺸴� ���� */
	glm::vec3 mLook = glm::vec3(0,0,0);
	/* ����, look �� ���� X */
	glm::quat mRotation = glm::quat(1,0,0,0);
	/* ��ü �� ȸ�� */
	glm::quat mModelRotation = glm::quat(1, 0, 0, 0);

	/* rotation(����) �߽� ��ǥ */
	const glm::vec3* mRotationPivot = nullptr;
	/* local rotation(������) �߽� ��ǥ */
	const glm::vec3* mLocalRotationPivot = nullptr;
	/* position �߽� ��ǥ */
	const glm::vec3* mPivot = nullptr;

	GLfloat mRoll = 0.0f;

public:
	Object();
	/* ������� �ʱ�ȭ */
	virtual GLvoid InitValues();

	//********** [ Position ] **********//
	/* mPosition�� const �ּ� ���� */
	inline constexpr const glm::vec3* GetRefPos() const { return &mPosition; }

	/* mPosition ���� */
	inline constexpr glm::vec3 GetPosition() const { return mPosition; }
	/* pivot�� ����� mPosition ���� */
	glm::vec3 GetPviotedPosition() const;

	inline constexpr GLvoid SetPosition(const glm::vec3& position) { mPosition = position; }
	inline constexpr GLvoid SetPosX(const GLfloat& x) { mPosition.x = x; }
	inline constexpr GLvoid SetPosY(const GLfloat& y) { mPosition.y = y; }
	inline constexpr GLvoid SetPosZ(const GLfloat& z) { mPosition.z = z; }

	GLvoid Move(const glm::vec3& vector, const GLboolean& applyTime = GL_TRUE);
	GLvoid MoveX(const GLfloat& amount, const GLboolean& applyTime = GL_TRUE);
	GLvoid MoveY(const GLfloat& amount, const GLboolean& applyTime = GL_TRUE);
	GLvoid MoveZ(const GLfloat& amount, const GLboolean& applyTime = GL_TRUE);
	/* look���� ���� ���� �۷ι� ��ǥ�迡�� �̵� */
	GLvoid MoveGlobal(const glm::vec3& vector, const GLboolean& applyTime = GL_TRUE);
	GLvoid SetPivot(const glm::vec3* pivot);
	inline constexpr const glm::vec3* GetPivot() const { return mPivot; }

	//********** [ Rotation ] **********//
	/* axis�� �������� ���� */
	GLvoid Rotate(const glm::vec3& axis, const GLfloat& degree);
	/* yaw(x��), pitch(y��), roll(z��) �� ���� ���� */
	GLvoid Rotate(const GLfloat& yaw, const GLfloat& pitch, const GLfloat& roll);
	/* mRotation�� axis�� �������� ȸ���ϴ� quaternion������ ���� */
	GLvoid SetRotation(const glm::vec3& axis, const GLfloat& degree);
	GLvoid SetRotation(const glm::quat& rotation);

	/* axis�� �������� ����, axis�� normal */
	GLvoid RotateLocal(const glm::vec3& axis, const GLfloat& degree);
	/* yaw(x��), pitch(y��), roll(z��) �� ���� ���� */
	GLvoid RotateLocal(const GLfloat& yaw, const GLfloat& pitch, const GLfloat& roll);
	/* mLocalRotation�� axis�� �������� ȸ���ϴ� quaternion������ ���� */
	GLvoid SetLocalRotation(const glm::vec3& axis, const GLfloat& degree);

	/* axis�� �������� �� ȸ�� */
	GLvoid RotateModel(const glm::vec3& axis, const GLfloat& degree);

	/* pivot ��ġ�� ���� axis�� �������� ���� */
	GLvoid RotatePivot(const glm::vec3& pivot, const glm::vec3& axis, const GLfloat& degree);
	/* pivot ��ġ�� ���� axis�� �������� ��ġ�� ���� */
	GLvoid RotatePosition(const glm::vec3& pivot, const glm::vec3& axis, const GLfloat& degree);
	
	GLvoid ResetRotation();
	GLvoid ResetModelRotation();
	glm::quat GetRotation() const;
	GLvoid SetRotationPivot(const glm::vec3* pivot);

	//********** [ Direction ] **********//
	/* look�� point�� �ٶ󺸵��� ���� */
	GLvoid Look(const glm::vec3& point);
	/* look�� �ش� ������ ���� */
	GLvoid SetLook(const glm::vec3& look);
	/* look�� �ش� look��ŭ ȸ��(Vector3::Up() ���� �ذ�) */
	GLvoid RotateLook(const glm::vec3& look);
		
	GLvoid ResetLook();

	glm::vec3 GetLook() const;
	glm::vec3 GetRight() const;
	glm::vec3 GetUp() const;
};

//////////////////////////////////////// [ SharedObject ] ////////////////////////////////////////
class ShaderObject abstract : public Object {
protected:
	/* ����ϴ� shader */
	Shader mShader = Shader::None;
	/* Object Color */
	MyColor mColor;

	/* Object ���� Scale�� */
	glm::vec3 mScale = { 0, 0, 0 };
	/* ���� ���� Scale��, ���� ��� X */
	glm::vec3 mScaleOrigin = { 0, 0, 0 };

	virtual GLvoid PrepareDraw() const;
public:
	ShaderObject();
	~ShaderObject();

	/* ī�޶�� �ָ� �ִ� ������� ���� */
	static bool CompareBlendObject(const ShaderObject* lhs, const ShaderObject* rhs);

	/* ������� �ʱ�ȭ */
	virtual GLvoid InitValues() override;

	//********** [ Scaling ] **********//
	GLvoid Scale(const GLfloat& scale);
	GLvoid SetScale(const GLfloat& scale);
	GLvoid ScaleOrigin(const GLfloat& scale);

	// [ WARNING ] //
	// ��յ� scale�� �𵨺�ȯ�� ������� ��ġ����� ����ؾ� �ϴ� ������ �ʿ��ϹǷ� ���� ��� ���� "��� ���͸� ����� ���" ������� �ʵ��� ��.
	GLvoid SetScaleX(const GLfloat& scale);
	GLvoid SetScaleY(const GLfloat& scale);
	GLvoid SetScaleZ(const GLfloat& scale);
	GLvoid SetScale(const glm::vec3& scale);
	GLvoid ScaleX(const GLfloat& amount);
	GLvoid ScaleY(const GLfloat& amount);
	GLvoid ScaleZ(const GLfloat& amount);
	//

	inline constexpr const glm::vec3* GetRefScale() const { return &mScale; };
	inline constexpr glm::vec3 GetScale() const { return mScale; }
	//

	//********** [ Size ] **********//
	virtual GLfloat GetWidth() const abstract;
	virtual GLfloat GetHeight() const abstract;
	virtual GLfloat GetDepth() const abstract;
	GLfloat GetRadius() const;
	/* Object�� 2D Rect (collision-box) ��ȯ */
	GLrect GetRect() const;

	//********** [ Transform ] **********//
	/* Object�� ���� Transform ���� */
	glm::mat4 GetTransform() const;
	/* Object�� ���� Transform ���� */
	GLvoid ModelTransform() const;
	/* Object�� �߾� ��ġ ���� */
	glm::vec3 GetCenterPos() const;

	/* Transform�� ����� mPosition ���� */
	inline glm::vec3 GetTransformedPos() const{ return glm::vec3(GetTransform() * glm::vec4(0, 0, 0, 1.0f)); }

	//********** [ Draw ] **********//
	virtual GLvoid Draw() const abstract;
	inline GLvoid SetColor(const COLORREF& color) { mColor = MyColor(color); }
	inline constexpr COLORREF GetColor() const { return mColor; }

	//********** [ Shader ] **********//
	inline constexpr Shader GetShader() const { return mShader; }
	inline constexpr GLvoid SetShader(const Shader& shader) { mShader = shader; }
};










/************************************************** [ MAJOR ROOTS ] **************************************************/

//////////////////////////////////////// [ IdentityObject ] ////////////////////////////////////////
// IdentityObject should BindBuffers() when generated
class IdentityObject abstract : public ShaderObject{
protected:
	GLuint mVAO = 0;
	GLuint mVBO[3] = { 0,0,0 };
	GLuint mEBO = 0;
	GLuint mTexture = 0;

	/* BindBuffers()�� ���� �Լ��� */
	virtual GLvoid PullVertices(vector<GLfloat>& vertices) const abstract;
	virtual GLvoid Pull_Indices_Vertex(vector<size_t>& indices_vertex) const abstract;
	virtual GLvoid PullColors(vector<GLfloat>& colors) const abstract;
	virtual GLvoid PullNormals(vector<GLfloat>& normals) const abstract;
	virtual GLvoid Pull_Indices_Normal(vector<size_t>& indices_normal) const abstract;
	virtual GLvoid PullUVs(vector<GLfloat>& uvs) const abstract;
	virtual GLvoid Pull_Indices_UV(vector<size_t>& indices_uv) const abstract;

	/* ��� ���� �ʱ�ȭ */
	virtual GLvoid InitValues() override;
public:
	IdentityObject();
	~IdentityObject();
	GLvoid InitBuffers();
	GLvoid BindBuffers();
	GLvoid DeleteBuffers();
	GLvoid SetTexture(const Textures& textureModel);

	// ���� ��� X //
	GLfloat GetWidth() const override;
	GLfloat GetHeight() const override;
	GLfloat GetDepth() const override;
	/////////////////

	//********** [ Buffer ] **********//
	/* Vertex Index ���� ���� */
	virtual size_t GetIndexCount() const abstract;
	/* Vertex ���� ���� */
	virtual size_t GetVertexCount() const abstract;

	inline constexpr const GLuint& GetVAO() const { return mVAO; }
	inline constexpr const GLuint& GetTexture() const { return mTexture; }
	inline MyColor GetColor() const { return mColor; }

	/* draw */
	virtual GLvoid Draw() const override;
};

//////////////////////////////////////// [ SharedObject ] ////////////////////////////////////////
class SharedObject : public ShaderObject {
protected:
	const IdentityObject* mObject = nullptr;
	GLboolean mIsChangeColor = GL_FALSE;

	GLuint mTexture = 0;
public:
	SharedObject() {};
	SharedObject(const IdentityObject* object);

	GLvoid Init(const IdentityObject* object);
	GLvoid Draw() const override;
	GLvoid SetTexture(const Textures& textureModel);

	inline GLfloat GetWidth() const override { return mObject->GetWidth(); }
	inline GLfloat GetHeight() const override { return mObject->GetHeight(); }
	inline GLfloat GetDepth() const override { return mObject->GetDepth(); }

	inline constexpr GLvoid SetObject(const IdentityObject* object) { mObject = object; }
	inline constexpr const IdentityObject* GetObject() const { return mObject; }
};











/************************************************** [ MINOR ROOTS ] **************************************************/

//////////////////////////////////////// [ ModelObject ] ////////////////////////////////////////
class ModelObject : public IdentityObject {
protected:
	const Model* mModel = nullptr;

	/* ModelObject������ ������� ���� */
	GLvoid PullColors(vector<GLfloat>& colors) const override {};

	GLvoid PullNormals(vector<GLfloat>& normals) const override;
	GLvoid PullVertices(vector<GLfloat>& vertices) const override;
	GLvoid Pull_Indices_Vertex(vector<size_t>& indices_vertex) const override;
	GLvoid Pull_Indices_Normal(vector<size_t>& indices_normal) const override;
	GLvoid PullUVs(vector<GLfloat>& textures) const override;
	GLvoid Pull_Indices_UV(vector<size_t>& indices_uv) const override;
public:
	ModelObject();
	ModelObject(const Model* model, const Shader& shader);
	GLvoid LoadModel(const Model* model, const Shader& shader);

	//********** [ Buffer ] **********//
	size_t GetIndexCount() const;
	size_t GetVertexCount() const;

	//********** [ Size ] **********//
	/* Side�� ���� �� ���� (Left -> ���� ��谪, Top -> ���� ��谪, ...) */
	GLfloat GetSide(const Dir& dir) const;
	GLfloat GetWidth() const override;
	GLfloat GetHeight() const override;
	GLfloat GetDepth() const override;

	//********** [ Collision ] **********//
	GLrect GetXZRect() const;
	set<glm::vec2, CompareSet> GetBoundings_XZ() const;
};

//////////////////////////////////////// [ CustomObject ] ////////////////////////////////////////
class CustomObject : public IdentityObject {
protected:
	vector<glm::vec3> mVertices;
	vector<size_t> mIndices;

	/* CustomObject������ ������� ���� */
	GLvoid PullNormals(vector<GLfloat>& normals) const override {};
	GLvoid Pull_Indices_Normal(vector<size_t>& indices_normal) const override {};
	GLvoid PullUVs(vector<GLfloat>& textures) const {};
	GLvoid Pull_Indices_UV(vector<size_t>& indices_uv) const {};

	GLvoid PullColors(vector<GLfloat>& colors) const override;
	GLvoid PullVertices(vector<GLfloat>& vertices) const override;
	GLvoid Pull_Indices_Vertex(vector<size_t>& indices_vertex) const override;
public:
	CustomObject();
	CustomObject(vector<glm::vec3>& vertices);
	CustomObject(vector<glm::vec3>& vertices, vector<size_t>& indices);

	//********** [ Buffer ] **********//
	size_t GetIndexCount() const;
	size_t GetVertexCount() const;
};











/************************************************** [ BASIC OBJECTS ] **************************************************/

//////////////////////////////////////// [ Line ] ////////////////////////////////////////
class LineObject : public CustomObject {
public:
	LineObject();
	LineObject(const glm::vec3& v1, const glm::vec3& v2);
	GLvoid Draw() const;
	GLvoid SetVertex(const GLboolean& index, const glm::vec3& pos);
};

//////////////////////////////////////// [ Triangle ] ////////////////////////////////////////
class TriangleObject : public CustomObject {
public:
	TriangleObject();
	TriangleObject(vector<glm::vec3>& vertices) : CustomObject(vertices) { if (vertices.size() != 3) assert(0); }
	GLvoid Draw() const;
};

//////////////////////////////////////// [ Plane ] ////////////////////////////////////////
class PlaneObject : public CustomObject {
public:
	PlaneObject();
	GLvoid Draw() const;
	glm::vec3 GetNormal() const;
	GLfloat CheckCollision(const glm::vec3& point, const GLfloat& radius) const;
};







/************************************************** [ COLLISION OBJECTS ] **************************************************/

//////////////////////////////////////// [ Cuboid ] ////////////////////////////////////////
class Cuboid {
private:
	const glm::vec3* mPosition = nullptr;
	const glm::vec3* mScale = nullptr;
	GLfloat mHalfWidth = 0.0f;
	GLfloat mHeight = 0.0f;
	GLfloat mHalfDepth = 0.0f;
public:
	Cuboid(const IdentityObject* object);
	Cuboid(const SharedObject* object, const GLfloat& width, const GLfloat& height, const GLfloat& depth);
	Cuboid(const glm::vec3* position, const glm::vec3* scale, const GLfloat& width, const GLfloat& height, const GLfloat& depth);

	GLvoid Draw() const;

	/* Side�� ���� �� ���� (Left -> ���� ��谪, Top -> ���� ��谪, ...) */
	GLfloat GetSide(const Dir& dir) const;
	/* GL_TRUE if collision */
	GLboolean CheckCollide(const glm::vec3& center, const GLfloat& radius = 0.0f) const;
	GLboolean CheckCollide(const GLrect& rect) const;

	GLrect GetXZRect() const;
};

//////////////////////////////////////// [ Circle ] ////////////////////////////////////////
class Circle {
private:
	SharedObject* mCircle = nullptr;

	glm::vec3 mOffset = { 0,0,0 };

	GLfloat mRadius = 0.0f;

	GLboolean mIsShadow = GL_FALSE;
public:
	Circle(const glm::vec3* pivot, const GLfloat& radius, const GLboolean& isShadow = GL_FALSE);

	GLvoid Draw() const;

	GLvoid SetColor(const COLORREF& color);
	glm::vec2 GetCenter() const;
	GLfloat GetRadius() const;
};

class PaintPlane;

/* 2D �浹üũ�� �ϴ� ��ü */
class ICollisionable_2D abstract {
private:
	CollisionType mCollisionType = CollisionType::None;

	GLint mID = -1;

	const glm::vec3* mPosition = nullptr;

	GLfloat mRadius = 0.0f;
	GLfloat mWidth = 0.0f;
	GLfloat mDepth = 0.0f;
public:
	virtual GLvoid SetCollision(const glm::vec3* position, const GLfloat& radius);
	virtual GLvoid SetCollision(const glm::vec3* position, const GLfloat& width, const GLfloat& depth);

	GLfloat GetRadius() const;
	GLfloat GetWidth() const;
	GLfloat GetDepth() const;

	inline constexpr CollisionType GetCollisionType() const{ return mCollisionType; }
	inline constexpr GLint Get_ID() const { return mID; }
};

class CollisionManager {
private:
	ICollisionable_2D* player = nullptr;
	vector<ICollisionable_2D*> mMonsterList;
	vector<ICollisionable_2D*> mObstacleList;
public:
	enum class Tag { Player, Monster, Obstacle };
	CollisionManager();
	~CollisionManager();

	GLvoid CheckCollisions();
	GLvoid AddObject(const Tag& tag, ICollisionable_2D* object);
	GLvoid DeleteObject(ICollisionable_2D* object);
};


/************************************************** [ OTHER OBJECTS ] **************************************************/
class PaintPlane : public SharedObject {
	GLfloat dt = 0.0f;
public:
	PaintPlane(const IdentityObject* object, const COLORREF& color, const glm::vec3& pos, const glm::vec3& normal);
	GLboolean Update();
};





GLvoid InitObject();
const LineObject* GetIdentityLine();
const ModelObject* GetIdentityModelObject(const Models& model);
const ModelObject* GetIdentityTextureObject(const Textures& textureModel);



GLvoid AddObject(const Shader& shader, ShaderObject* object);
GLvoid AddBlendObject(ShaderObject* object);
GLvoid DeleteBlendObject(ShaderObject* object);
GLvoid DeleteObject(const Shader& shader, ShaderObject* object);
GLvoid DeleteObjects();
GLvoid DrawObjects(const Shader& shader);
GLvoid DrawBlendObjects();

////////// [ DEBUG ] //////////
GLvoid DrawDebugWireXZ(const set<glm::vec2, CompareSet>& vertices, GLfloat yPos, const COLORREF& color = RED, const glm::vec3* pivot = nullptr);