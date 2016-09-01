<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:docbook="http://docbook.org/ns/docbook"
  exclude-result-prefixes="docbook"
  version="1.0">

<!--
This XSLT stylesheet illustrates how to render the same Islandora XML object
based on URL parameters passed into the stylesheet.
-->

  <xsl:output method="html" indent="yes"/>
  <xsl:param name="chapter"></xsl:param>
  <xsl:param name="pid"></xsl:param>

  <xsl:template match="docbook:book">
    <div>
    <xsl:apply-templates select="docbook:chapter"/>
    </div>
    <xsl:apply-templates select="docbook:bookinfo"/>
  </xsl:template>

  <xsl:template match="docbook:chapter">

     <!-- If the 'chapter' parameter is not present, build a table of contents with links to each chapter. -->
     <xsl:if test="not($chapter)">
       <p><a href="/islandora/object/{$pid}?chapter={./@xml:id}"><xsl:value-of select="docbook:title"/></a></p>
     </xsl:if>

     <!-- If the 'chapter' URL parameter contains a chapter ID, render the chapter. -->
     <xsl:if test="$chapter">
       <xsl:if test="./@xml:id=$chapter">
         <h2><xsl:value-of select="docbook:title"/></h2>
          <xsl:for-each select="docbook:para">
            <p><xsl:value-of select="."/></p>
          </xsl:for-each>
          <div><a href="/islandora/object/{$pid}">Table of contents</a></div>
       </xsl:if>
     </xsl:if>

    <!-- If the chapter ID is 'all', render the whole document. -->
    <xsl:if test="$chapter='all'">
      <h2><xsl:value-of select="docbook:title"/></h2>
      <xsl:for-each select="docbook:para">
        <p><xsl:value-of select="."/></p>
      </xsl:for-each>
      <div><a href="/islandora/object/{$pid}">Table of contents</a></div>
    </xsl:if>

  </xsl:template>

  <xsl:template match="docbook:bookinfo">
    <h3>Copyright</h3>
    <div><xsl:value-of select="docbook:legalnotice/docbook:para"/></div>
  </xsl:template>

</xsl:stylesheet>
