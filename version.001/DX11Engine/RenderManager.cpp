#include "pch.h"
#include "RenderManager.h"
#include "Pipeline.h"
#include "MeshRenderer.h"
#include "Animator.h"
#include "Mesh.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Core.h"
#include "GameObject.h"

RenderManager::RenderManager(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: _device(device), _deviceContext(deviceContext)
{
}

void RenderManager::Init()
{
	_pipeline = make_shared<Pipeline>(_deviceContext);

	_transformBuffer = std::make_shared<ConstantBuffer<TransformData>>(_device, _deviceContext);
	_transformBuffer->Create();
	_cameraBuffer = std::make_shared<ConstantBuffer<CameraData>>(_device, _deviceContext);
	_cameraBuffer->Create();
	_animationBuffer = std::make_shared<ConstantBuffer<AnimationData>>(_device, _deviceContext);
	_animationBuffer->Create();

	_rasterizerState = std::make_shared<RasterizerState>(_device);
	_rasterizerState->Create();
	_blendState = std::make_shared<BlendState>(_device);
	_blendState->Create();
	_samplerState = std::make_shared<SamplerState>(_device);
	_samplerState->Create();

}

void RenderManager::Update(shared_ptr<Graphics> graphics)
{
	graphics->RenderBegin();

	PushCameraData();
	GatherRenderableObjects();
	RenderObjects();

	graphics->RenderEnd();
}

void RenderManager::PushCameraData()
{
	_cameraData.view = Camera::View;
	_cameraData.projection = Camera::Projection;
	_cameraBuffer->CopyData(_cameraData);
}

void RenderManager::PushTransformData()
{
	_transformBuffer->CopyData(_transformData);
}

void RenderManager::PushAnimationData()
{
	_animationBuffer->CopyData(_animationData);
}

void RenderManager::GatherRenderableObjects()
{
	_renderObjects.clear();

	auto& gameObjects = SCENE->GetActiveScene()->GetGameObjects();

	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		shared_ptr<MeshRenderer> meshRenderer = static_pointer_cast<MeshRenderer>(gameObject->GetFixedComponent(ComponentType::MeshRenderer));
		if (meshRenderer)
			_renderObjects.push_back(gameObject);
	}
}

void RenderManager::RenderObjects()
{
	for (const shared_ptr<GameObject>& gameObject : _renderObjects)
	{
		shared_ptr<MeshRenderer> meshRenderer = static_pointer_cast<MeshRenderer>(gameObject->GetFixedComponent(ComponentType::MeshRenderer));
		if (meshRenderer == nullptr)
			continue;

		shared_ptr<Transform> transform = gameObject->GetTransform();

		if (transform == nullptr)
			continue;

		// SRT
		_transformData.world = transform->GetWorld();
		PushTransformData();

		// Animation
		shared_ptr<Animator> animator = static_pointer_cast<Animator>(gameObject->GetFixedComponent(ComponentType::Animator));
		if (animator)
		{
			const Keyframe& keyframe = animator->GetCurrentKeyframe();
			_animationData.spriteOffset = keyframe.offset;
			_animationData.spriteSize = keyframe.size;
			_animationData.textureSize = animator->GetCurrentAnimation()->GetTextureSize();
			_animationData.useAnimation = 1.0f;
			PushAnimationData();

			_pipeline->SetConstantBuffer(2, ShaderScope_VertexShader, _animationBuffer);
			_pipeline->SetTexture(0, ShaderScope_PixelShader, animator->GetCurrentAnimation()->GetTexture());
		}
		else
		{
			_animationData.spriteOffset = { 0.f, 0.f };
			_animationData.spriteSize = { 0.f, 0.f };
			_animationData.textureSize = { 0.f, 0.f };
			_animationData.useAnimation = 0.0f;
			PushAnimationData();

			_pipeline->SetConstantBuffer(2, ShaderScope_VertexShader, _animationBuffer);
			_pipeline->SetTexture(0, ShaderScope_PixelShader, meshRenderer->GetTexture());
		}

		PipelineInfo info;
		info.inputLayout = meshRenderer->GetInputLayout();
		info.vertexShader = meshRenderer->GetVertexShader();
		info.pixelShader = meshRenderer->GetPixelShader();
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;
		_pipeline->UpdatePipeline(info);

		_pipeline->SetVertexBuffer(meshRenderer->GetMesh()->GetVertexBuffer());
		_pipeline->SetIndexBuffer(meshRenderer->GetMesh()->GetIndexBuffer());
		_pipeline->SetConstantBuffer(1, ShaderScope_VertexShader, _cameraBuffer);
		_pipeline->SetConstantBuffer(0, ShaderScope_VertexShader, _transformBuffer);
		//_pipeline->SetTexture(0, ShaderScope_PixelShader, meshRenderer->GetTexture());
		_pipeline->SetSamplerState(0, ShaderScope_PixelShader, _samplerState);

		_pipeline->DrawIndexed(meshRenderer->GetMesh()->GetIndexBuffer()->GetCount(), 0, 0);
	}
}
