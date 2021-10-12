#

## Nodes

LINE = {(TEXT | LINK | TEMPLATE)+}
LAYOUT = {(LAYOUT | LINE)+}
TEMPLATE = ((NAME) | (VALUE))+

LISTITEM = {(ENTITY)+}

## Conversion
### Converting template to html
When a template is inside a layout or a text or a link or a value, it is meant to be displayed. 

It can be used with either a custom tag or a span element.

If we decide to use "span" elment.

<span type="template" lang="en">Johny English</span>

And the last value should be a text node of a span element

## JSON Format

The purpose of using unified "property" object is that it could be simpler for programming language to loop through key and value pair easily. 

{
    "article": {
        "templates": [
            {
                "order": 0,
                "name": "",
                "properties": [
                    {
                        "name": "",
                        "value": ""
                    },
                    ...
                ],
                ...
            },
            {
                "order": 1,
                "properties": [
                    {
                        "name": "",
                        "value": ""
                    },
                    ...
                ],
                ...
            },
            ...
        ],        
        "sections": [
            {
                "id": 0,
                "text": "the first paragraph for short introduction of the topic",
                "order": 2 // based on the appearance
            },
            {
                "id": 1,
                "text": "the first section",
                "level": "2",
                "line": "the section title",
                "order": 3
            }
        ]
    }
}