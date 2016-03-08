This directory contains stylesheets that are not used by the Islandora XML Solution Pack directly but that might be of interests to some users.

Both XSLT stylesheets are designed to work with simple, flat XML OBJ datastreams like this:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<person>
 <name displayLabel="Name">Osler, Marian Frances</name>
 <birth_place displayLabel="Birth place">Fredericton, New Brunswick</birth_place>
 <date_of_birth displayLabel="Birth date">25 September 1842</date_of_birth>
 <occupation displayLabel="Occupation">Writer</occupation>
</person>
```

However, it is possible to create more sophisticated stylesheets to suite more complex XML.
