/** 
 * XMLSec library
 *
 *
 * See Copyright for the status of this software.
 * 
 * Author: Aleksey Sanin <aleksey@aleksey.com>
 */
#ifndef __XMLSEC_LIST_H__
#define __XMLSEC_LIST_H__    

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */ 

#include <xmlsec/xmlsec.h>
#include <xmlsec/buffer.h>

typedef const struct _xmlSecPtrListKlass			xmlSecPtrListKlass, 
								*xmlSecPtrListId;
typedef struct _xmlSecPtrList 					xmlSecPtrList, 
								*xmlSecPtrListPtr;
/**
 * xmlSecPtr:
 *
 * Void pointer.
 */
typedef void*	xmlSecPtr;


/**
 * xmlSecPtrList:
 * @id:				the list items description.
 * @data:			the list data.
 * @use:			the current list size.
 * @max:			the max (allocated) list size.
 * @allocMode:			the memory allocation mode.
 * 
 * The pointers list.
 */
struct _xmlSecPtrList {
    xmlSecPtrListId		id;        

    xmlSecPtr*			data;
    size_t			use;
    size_t			max;
    xmlSecAllocMode 		allocMode;
};

XMLSEC_EXPORT void		xmlSecPtrListSetDefaultAllocMode(xmlSecAllocMode defAllocMode,
								 size_t defInitialSize);


XMLSEC_EXPORT int		xmlSecPtrListInitialize		(xmlSecPtrListPtr list,
								 xmlSecPtrListId id);
XMLSEC_EXPORT void		xmlSecPtrListFinalize		(xmlSecPtrListPtr list);
XMLSEC_EXPORT xmlSecPtrListPtr	xmlSecPtrListCreate		(xmlSecPtrListId id);
XMLSEC_EXPORT void		xmlSecPtrListDestroy		(xmlSecPtrListPtr list);

XMLSEC_EXPORT int		xmlSecPtrListCopy		(xmlSecPtrListPtr dst,
								 xmlSecPtrListPtr src);
XMLSEC_EXPORT xmlSecPtrListPtr	xmlSecPtrListDuplicate		(xmlSecPtrListPtr list);

XMLSEC_EXPORT size_t		xmlSecPtrListGetSize		(xmlSecPtrListPtr list);
XMLSEC_EXPORT xmlSecPtr		xmlSecPtrListGetItem		(xmlSecPtrListPtr list,
							         size_t pos);
XMLSEC_EXPORT int		xmlSecPtrListAdd		(xmlSecPtrListPtr list,
								 xmlSecPtr item);
XMLSEC_EXPORT int		xmlSecPtrListSet		(xmlSecPtrListPtr list,
								 xmlSecPtr item,
								 size_t pos);
XMLSEC_EXPORT int		xmlSecPtrListRemove		(xmlSecPtrListPtr list,
							    	 size_t pos);
XMLSEC_EXPORT void		xmlSecPtrListDebugDump		(xmlSecPtrListPtr list,
    								 FILE* output);
XMLSEC_EXPORT void		xmlSecPtrListDebugXmlDump	(xmlSecPtrListPtr list,
 								 FILE* output);

/**
 * xmlSecPtrListGetName:
 * @list: 		the ponter to list.
 * 
 * Macro. Returns lists's name.
 */
#define xmlSecPtrListGetName(list) \
	(((list) != NULL) ? xmlSecPtrListKlassGetName((list)->id) : NULL)

/**
 * xmlSecPtrListIsValid:
 * @list: 		the pointer to list.
 *
 * Macro. Returns 1 if @list is not NULL and @list->id is not NULL
 * or 0 otherwise.
 */ 
#define xmlSecPtrListIsValid(list) \
	((( list ) != NULL) && ((( list )->id) != NULL))
/**
 * xmlSecPtrListCheckId:
 * @list: 		the pointer to list.
 * @dataId: 		the list Id.
 *
 * Macro. Returns 1 if @list is valid and @list's id is equal to @dataId.
 */
#define xmlSecPtrListCheckId(list, dataId) \
 	(xmlSecPtrListIsValid(( list )) && \
	((( list )->id) == ( dataId )))


/**************************************************************************
 *
 * xmlSecPtrListKlass
 *
 *************************************************************************/
/**
 * xmlSecPtrListIdUnknown:
 *
 * The "unknown" id.
 */
#define xmlSecPtrListIdUnknown 			NULL

typedef xmlSecPtr		(*xmlSecPtrDuplicateItemMethod)	(xmlSecPtr ptr);
typedef void			(*xmlSecPtrDestroyItemMethod)	(xmlSecPtr ptr);
typedef void			(*xmlSecPtrDebugDumpItemMethod)	(xmlSecPtr ptr,
								 FILE* output);

struct _xmlSecPtrListKlass {
    const xmlChar*			name;
    xmlSecPtrDuplicateItemMethod	duplicateItem;
    xmlSecPtrDestroyItemMethod		destroyItem;
    xmlSecPtrDebugDumpItemMethod	debugDumpItem;
    xmlSecPtrDebugDumpItemMethod	debugXmlDumpItem;
};
#define xmlSecPtrListKlassGetName(klass) \
	(((klass) != NULL) ? ((klass)->name) : NULL)


/**************************************************************************
 *
 * xmlSecStaticObjectListKlass:
 *
 *************************************************************************/
#define xmlSecStaticObjectListId \
	xmlSecStaticObjectListGetKlass()
XMLSEC_EXPORT xmlSecPtrListId	xmlSecStaticObjectListGetKlass	(void);

/**************************************************************************
 *
 * xmlSecStringListKlass
 *
 *************************************************************************/
#define xmlSecStringListId \
	xmlSecStringListGetKlass()
XMLSEC_EXPORT xmlSecPtrListId	xmlSecStringListGetKlass	(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __XMLSEC_LIST_H__ */

