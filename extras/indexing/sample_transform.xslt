<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:xlink="http://www.w3.org/1999/xlink"
  xmlns:foxml="info:fedora/fedora-system:def/foxml#">

  <!-- @todo: Figure out how allow specific indexing for collections, etc.
       so that not all the simple XML objects are indexed using this same stylesheet.
        Maybe require a namespace in the XML?i -->
  <xsl:template match="foxml:datastream[@ID='OBJ']/foxml:datastreamVersion[last() and @MIMETYPE='application/xml']" name="index_ceww">
    <xsl:param name="content"/>
    <xsl:param name="prefix">ceww_</xsl:param>
    <xsl:param name="suffix">_ms</xsl:param>

    <!-- 'writer' is the document element of the simple XML objects. -->
    <xsl:for-each select="$content/writer/*">
      <field>
        <xsl:attribute name="name">
          <xsl:value-of select="concat($prefix, local-name(), $suffix)"/>
        </xsl:attribute>
        <xsl:value-of select="text()"/>
      </field>
    </xsl:for-each>
  </xsl:template>
</xsl:stylesheet>
