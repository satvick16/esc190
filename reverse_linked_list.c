ListNode *reverse(ListNode *ll) {
	ListNode *left = NULL;
	ListNode *curr = ll;
	ListNode *right = NULL;

	while (curr != NULL) {
		// hold rest of list
		right = curr->next;

		// make current->next to be previous
		curr->next = left;

		// moving pointers forward
		left = curr
		curr = right;
	}

	return left;
}