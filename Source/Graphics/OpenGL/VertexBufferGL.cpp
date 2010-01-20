#include <Pxf/Pxf.h>
#include <Pxf/Util/String.h>
#include <Pxf/Graphics/OpenGL/VertexBufferGL.h>
#include <Pxf/Graphics/PrimitiveType.h>
#include <Pxf/Base/Debug.h>
#include <Pxf/Base/Utils.h>

#define LOCAL_MSG "VertexBufferGL"

using namespace Pxf;
using namespace Pxf::Graphics;
using Util::String;

VertexBufferGL::VertexBufferGL(void *_Data, unsigned int _Offset, unsigned int _VerticeCount, GLenum _Usage)
{
	//
	if(_Data)
		m_VBuffer	= _Data;
	else
		Message(LOCAL_MSG,"Unable to create Vertex Buffer with empty data");

	m_IsLocked		= false;
	m_Stride		= _Offset;
	m_VCount		= _VerticeCount;
	m_UsageFlag		= _Usage;
	m_PrimitiveMode	= 0;

	CreateVBO();
}

VertexBufferGL::~VertexBufferGL()
{
	//
	SafeDeleteArray(m_VBuffer);
	DestroyVBO();
}

bool VertexBufferGL::DestroyVBO()
{
	if(!IsLocked())
	{
		Unbind();
		glDeleteBuffersARB(1,&m_VBOID);
		return true;
	}
	else
		// now what? :( 
		return false;
	
}

bool VertexBufferGL::CreateVBO()
{
	glGenBuffersARB(1, &m_VBOID);
	
	if(!IsBound())
	{
		// lock
		Bind();
		// upload data
		// need to know vertex format before we can write the data to the graphics card..
		//glBufferDataARB(GL_ARRAY_BUFFER_ARB, dataSize, m_VBuffer, m_UsageFlag);
		Unbind();
		// unlock
		return true;
	}
	else
	{
		Message(LOCAL_MSG,"Unable to write data to a bound buffer");
		return false;
	}
}

void VertexBufferGL::Bind()
{
	if(IsBound())
		return;

	if(!IsLocked())
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VBOID);
		m_Bound = true;
	}
	else
		Message(LOCAL_MSG,"Unable to Bind a locked buffer");
}

void VertexBufferGL::Unbind()
{
	if(!IsBound())
		return;

	if(!IsLocked())
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		m_Bound = false;
	}
	else
		Message(LOCAL_MSG,"Unable to unbind locked buffer");
}

VertexBuffer& VertexBufferGL::Lock()
{
	// ?? :S
	m_IsLocked = true;
	return *this;
}

VertexBuffer& VertexBufferGL::Unlock()
{
	// ?? :S
	m_IsLocked = false;
	return *this;
}

PrimitiveType VertexBufferGL::GetPrimitive()
{
	switch(m_PrimitiveMode)
	{
		// might be wrong or something missing
		case(GL_POINTS): return EPointList;
		case(GL_LINES):	return ELineList;
		case(GL_LINE_STRIP): return ELineStrip;
		case(GL_TRIANGLES): return ETriangleList;
		case(GL_TRIANGLE_STRIP): return ETriangleStrip;
		case(GL_TRIANGLE_FAN): return ETriangleFan;
	}

	// default enum (is there a better solution?:E)
	return EUnknown;
}

void VertexBufferGL::SetPrimitive(PrimitiveType _PrimitiveType)
{
	switch(_PrimitiveType)
	{
		case(EPointList): m_PrimitiveMode = GL_POINTS;
		case(ELineList): m_PrimitiveMode = GL_LINES;
		case(ELineStrip): m_PrimitiveMode = GL_LINE_STRIP;
		case(ETriangleList): m_PrimitiveMode = GL_TRIANGLES;
		case(ETriangleStrip): m_PrimitiveMode = GL_TRIANGLE_STRIP;
		case(ETriangleFan): m_PrimitiveMode = GL_TRIANGLE_FAN;
	}
}


