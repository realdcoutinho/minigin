float4x4 gWorldViewProj : WorldViewProjection;
float4x4 gViewInverse : ViewInverse;
float4x4 gWord : World;
float4x4 gRotationYMatrix;
Texture2D gParticleTexture;


SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = WRAP;
    AddressV = WRAP;
};

//STATES
//******
BlendState AlphaBlending 
{     
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
	BlendOp = ADD;
	SrcBlendAlpha = ONE;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
	RenderTargetWriteMask[0] = 0x0f;
};

DepthStencilState DisableDepthWriting
{
	//Enable Depth Rendering
	DepthEnable = TRUE;
	//Disable Depth Writing
	DepthWriteMask = ZERO;
};

RasterizerState BackCulling
{
	CullMode = BACK;
};


//SHADER STRUCTS
//**************
struct VS_DATA
{
	float3 Position : POSITION;
	float4 Color: COLOR;
	float Size: TEXCOORD0;
	float Rotation: TEXCOORD1;
};

struct GS_DATA
{
	float4 Position : SV_POSITION;
	float2 TexCoord: TEXCOORD0;
	float4 Color : COLOR;
};

//VERTEX SHADER
//*************
VS_DATA MainVS(VS_DATA input)
{
	return input;
}

//GEOMETRY SHADER
//***************
void CreateVertex(inout TriangleStream<GS_DATA> triStream, float3 pos, float2 texCoord, float4 col, float2x2 uvRotation)
{
	//Step 1. Create a GS_DATA object
	GS_DATA data;
	//Step 2. Transform the position using the WVP Matrix and assign it to (GS_DATA object).Position (Keep in mind: float3 -> float4, Homogeneous Coordinates)
	float4 position = mul(float4(pos, 1.0f), gWorldViewProj);
	//Step 3. Assign texCoord to (GS_DATA object).TexCoord
		//This is a little formula to do texture rotation by transforming the texture coordinates (Can cause artifacts)

	//Step 4. Assign color to (GS_DATA object).Color
	float4 color = col;
	//Step 5. Append (GS_DATA object) to the TriangleStream parameter (TriangleStream::Append(...))

	data.Position = position;
	data.TexCoord = texCoord;
	data.Color = color;
	
	//TEMP
	triStream.Append(data); //Remove this line
}

[maxvertexcount(4)]
void MainGS(point VS_DATA vertex[1], inout TriangleStream<GS_DATA> triStream)
{
	//Use these variable names
	float3 topLeft, topRight, bottomLeft, bottomRight;
	float size = vertex[0].Size;
	float3 origin = vertex[0].Position;

	//Vertices (Keep in mind that 'origin' contains the center of the quad
	float offset = size / 2;
	topLeft = float3(origin.x - offset, origin.y + offset, origin.z);
	topRight = float3(origin.x + offset, origin.y + offset, origin.z);
	bottomLeft = float3(origin.x - offset, origin.y - offset, origin.z);
	bottomRight = float3(origin.x + offset, origin.y - offset, origin.z);

	//Transform the vertices using the ViewInverse (Rotational Part Only!!! (~ normal transformation)), this will force them to always point towards the camera (cfr. BillBoarding)
	// use float3x3 so to only apply rotation
	// 
	// 
	//HERE APPLY THE ROTAYION MATRIX YOU WISH

		//topLeft = mul(topLeft, (float3x3)gRotationYMatrix);
		//topRight = mul(topRight, (float3x3)gRotationYMatrix);
		//bottomLeft = mul(bottomLeft, (float3x3)gRotationYMatrix);
		//bottomRight = mul(bottomRight, (float3x3)gRotationYMatrix);



	//This is the 2x2 rotation matrix we need to transform our TextureCoordinates (Texture Rotation)
	float2x2 uvRotation = {cos(vertex[0].Rotation), - sin(vertex[0].Rotation), sin(vertex[0].Rotation), cos(vertex[0].Rotation)};
	
	//Create Geometry (Trianglestrip)
	CreateVertex(triStream,bottomLeft, float2(0,1), vertex[0].Color, uvRotation);
	CreateVertex(triStream,topLeft, float2(0,0), vertex[0].Color, uvRotation);
	CreateVertex(triStream,bottomRight, float2(1,1), vertex[0].Color, uvRotation);
	CreateVertex(triStream,topRight, float2(1,0), vertex[0].Color, uvRotation);
}

//PIXEL SHADER
//************
float4 MainPS(GS_DATA input) : SV_TARGET {
	
	//Simple Texture Sampling
	float4 result = gParticleTexture.Sample(samPoint,input.TexCoord);
	return input.Color * result;
}

// Default Technique
technique10 Default {

	pass p0 {
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetGeometryShader(CompileShader(gs_4_0, MainGS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
		
		SetRasterizerState(BackCulling);       
		SetDepthStencilState(DisableDepthWriting, 0);
        SetBlendState(AlphaBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF);
	}
}
