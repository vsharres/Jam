#pragma once

#include "SceneViewport.h"

class FDatabaseViewerViewportClient : public FEditorViewportClient
{
public:
	explicit FDatabaseViewerViewportClient(const TWeakPtr<class SEditorViewport>& InEditorViewportWidget = nullptr);
	~FDatabaseViewerViewportClient();

	// FViewportClient interface
	virtual void Tick(float DeltaSeconds) override;
	// End of FViewportClient interface

	// FEditorViewportClient interface
	virtual FLinearColor GetBackgroundColor() const override;
	// End of FEditorViewportClient interface

	// FSerializableObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	// End of FSerializableObject interface





};
