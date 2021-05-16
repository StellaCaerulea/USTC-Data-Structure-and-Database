/* queueLinked.h */
#ifndef _QUEUE_LINKED_H_
#define _QUEUE_LINKED_H_

#include <stdlib.h>
#include <errno.h>

#ifndef TYPE_ELEM_Q_DEFINED
	typedef int typeElemQ;
	#define TYPE_ELEM_Q_STD_ERR 0
#endif

typedef struct NodeQ
{
	typeElemQ data;
	struct NodeQ *next;
} nodeQ;

typedef struct QueueLinked
{
	nodeQ *front;
	nodeQ *rear;

} queueLinked;

queueLinked *queueInit(void)
{
	queueLinked *ret = (queueLinked *)malloc(sizeof(queueLinked));
	ret->front = NULL;
	ret->rear = NULL;
	return ret;
}

errno_t queueEn(queueLinked *q, typeElemQ e)
{
	nodeQ *n = (nodeQ *)malloc(sizeof(nodeQ));

	if (n == NULL)
	{
		return -ENOMEM;
	}
	else
	{
		n->data = e;
		n->next = NULL;

		if (q->rear == NULL)
		{
			q->rear = n;
			q->front = n;
			return 0;
		}
		else
		{
			q->rear->next = n;
			q->rear = n;
			return 0;
		}
	}
}

typeElemQ queueDe(queueLinked *q)
{
	if (q == NULL)
	{
		return TYPE_ELEM_Q_STD_ERR;
	}
	else if (q->front == NULL)
	{
		return TYPE_ELEM_Q_STD_ERR;
	}
	else
	{
		typeElemQ ret = q->front->data;
		nodeQ *n = q->front;
		q->front = q->front->next;
		free(n);
		if (q->front == NULL)
		{
			q->rear = NULL;
		}
		return ret;
	}
}

#endif
