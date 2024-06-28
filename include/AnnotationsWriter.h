#pragma once

#include <list>

#include "PDFPage.h"
#include "DictionaryContext.h"
#include "DocumentContextExtenderAdapter.h"

class ObjectsContext;

class AnnotationsWriter : public DocumentContextExtenderAdapter
{

public:

    AnnotationsWriter(void);

    void AddCopiedAnnotation(ObjectIDType inNewAnnotation);

    EStatusCode OnPageWrite
    (
        PDFPage* inPage,
        DictionaryContext* inPageDictionaryContext,
        ObjectsContext* inPDFWriterObjectContext,
        DocumentContext* inPDFWriterDocumentContext
    );

private:

    std::list<ObjectIDType> mAnnotationsIDs;
};