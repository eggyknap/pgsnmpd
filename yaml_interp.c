
void process_event(yaml_event_t *event) {
    switch (event->type) {
        case YAML_NO_EVENT:
            printf("YAML_NO_EVENT\n");
            break;
        case YAML_STREAM_START_EVENT:
            printf("YAML_STREAM_START_EVENT\n");
            switch (event->data.stream_start.encoding) {
                case YAML_ANY_ENCODING:
                    printf("\tYAML_ANY_ENCODING\n");
                    break;
                case YAML_UTF8_ENCODING:
                    printf("\tYAML_UTF8_ENCODING\n");
                    break;
                case YAML_UTF16LE_ENCODING:
                    printf("\tYAML_UTF16LE_ENCODING\n");
                    break;
                case YAML_UTF16BE_ENCODING:
                    printf("\tYAML_UTF16BE_ENCODING\n");
                    break;
            }
            break;
        case YAML_STREAM_END_EVENT:
            printf("YAML_STREAM_END_EVENT\n");
            break;
        case YAML_DOCUMENT_START_EVENT:
            printf("YAML_DOCUMENT_START_EVENT\n");
            if (event->data.document_start.version_directive != NULL) {
                printf("\tVersion directive: %d.%d\n",
                    event->data.document_start.version_directive->major,
                    event->data.document_start.version_directive->minor);
            }
            printf("\t\"document indicator\" is %simplicit, whatever that means\n", event->data.document_start.implicit ? "" : "not ");
            if (event->data.document_start.tag_directives.start != NULL) {
                printf("\tTag directives start: tag handle: %s\t\ttag prefix: %s\n",
                    event->data.document_start.tag_directives.start->handle,
                    event->data.document_start.tag_directives.start->prefix);
            }
            if (event->data.document_start.tag_directives.end != NULL) {
                printf("\tTag directives end: tag handle: %s\t\ttag prefix: %s\n",
                    event->data.document_start.tag_directives.end->handle,
                    event->data.document_start.tag_directives.end->prefix);
            }
            break;
        case YAML_DOCUMENT_END_EVENT:
            printf("YAML_DOCUMENT_END_EVENT\n");
            printf("\t\"document indicator\" is %simplicit, whatever that means\n", event->data.document_end.implicit ? "" : "not ");
            break;
        case YAML_ALIAS_EVENT:
            printf("YAML_ALIAS_EVENT\n");
            if (event->data.alias.anchor != NULL) {
                printf("\tAnchor: %s\n", event->data.alias.anchor);
            }
            break;
        case YAML_SCALAR_EVENT:
            printf("YAML_SCALAR_EVENT\n");
            if (event->data.scalar.anchor != NULL)
                printf("\tAnchor: %s\n", event->data.scalar.anchor);
            if (event->data.scalar.tag != NULL)
                printf("\tTag: %s\n", event->data.scalar.tag);
            if (event->data.scalar.value != NULL)
                printf("\tValue: %s\n", event->data.scalar.value);
            printf("\tLength: %d\n", event->data.scalar.length);
            printf("\t\"plain_implicit\" is %simplicit, whatever that means\n", event->data.scalar.plain_implicit ? "" : "not ");
            printf("\t\"quoted_implicit\" is %simplicit, whatever that means\n", event->data.scalar.quoted_implicit ? "" : "not ");
            switch (event->data.scalar.style) {
                case YAML_ANY_SCALAR_STYLE:
                    printf("\tYAML_ANY_SCALAR_STYLE\n");
                    break;
                case YAML_PLAIN_SCALAR_STYLE:
                    printf("\tYAML_PLAIN_SCALAR_STYLE\n");
                    break;
                case YAML_SINGLE_QUOTED_SCALAR_STYLE:
                    printf("\tYAML_SINGLE_QUOTED_SCALAR_STYLE\n");
                    break;
                case YAML_DOUBLE_QUOTED_SCALAR_STYLE:
                    printf("\tYAML_DOUBLE_QUOTED_SCALAR_STYLE\n");
                    break;
                case YAML_LITERAL_SCALAR_STYLE:
                    printf("\tYAML_LITERAL_SCALAR_STYLE\n");
                    break;
                case YAML_FOLDED_SCALAR_STYLE:
                    printf("\tYAML_FOLDED_SCALAR_STYLE\n");
                    break;
            }
            break;
        case YAML_SEQUENCE_START_EVENT:
            printf("YAML_SEQUENCE_START_EVENT\n");
            if (event->data.sequence_start.anchor != NULL)
                printf("\tAnchor: %s\n", event->data.sequence_start.anchor);
            if (event->data.sequence_start.tag != NULL)
                printf("\tTag: %s\n", event->data.sequence_start.tag);
            printf("\ttag is %simplicit, whatever that means\n", event->data.sequence_start.implicit ? "" : "not ");
            switch (event->data.sequence_start.style) {
                case YAML_ANY_SEQUENCE_STYLE:
                    printf("\tYAML_ANY_SEQUENCE_STYLE\n");
                    break;
                case YAML_BLOCK_SEQUENCE_STYLE:
                    printf("\tYAML_BLOCK_SEQUENCE_STYLE\n");
                    break;
                case YAML_FLOW_SEQUENCE_STYLE:
                    printf("\tYAML_FLOW_SEQUENCE_STYLE\n");
                    break;
            }
            break;
        case YAML_SEQUENCE_END_EVENT:
            printf("YAML_SEQUENCE_END_EVENT\n");
            break;
        case YAML_MAPPING_START_EVENT:
            printf("YAML_MAPPING_START_EVENT\n");
            if (event->data.mapping_start.anchor != NULL)
                printf("\tAnchor: %s\n", event->data.mapping_start.anchor);
            if (event->data.mapping_start.tag != NULL)
                printf("\tTag: %s\n", event->data.mapping_start.tag);
            printf("\tmapping is %simplicit, whatever that means\n", event->data.mapping_start.implicit ? "" : "not ");
            switch (event->data.sequence_start.style) {
                case YAML_ANY_MAPPING_STYLE:
                    printf("\tYAML_ANY_MAPPING_STYLE\n");
                    break;
                case YAML_BLOCK_MAPPING_STYLE:
                    printf("\tYAML_BLOCK_MAPPING_STYLE\n");
                    break;
                case YAML_FLOW_MAPPING_STYLE:
                    printf("\tYAML_FLOW_MAPPING_STYLE\n");
                    break;
            }
            break;
        case YAML_MAPPING_END_EVENT:
            printf("YAML_MAPPING_END_EVENT\n");
            break;
    };
}


